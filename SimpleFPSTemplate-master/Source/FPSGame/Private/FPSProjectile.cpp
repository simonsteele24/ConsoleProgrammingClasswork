// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Cube.h"

AFPSProjectile::AFPSProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Adds a randomized explosion effectand destroys a given actor
void AFPSProjectile::Explode(AActor* otherActor)
{
	float randomScale = FMath::RandRange(ExplosionSizeMinimum, ExplosionSizeMaximum); // Randomize explosion size
	UParticleSystemComponent * ps = UGameplayStatics::SpawnEmitterAtLocation(this, explosionTemplate, GetActorLocation()); // Create particle emitter
	ps->SetWorldScale3D(FVector(randomScale)); // Set the effect based on the randomized size
	otherActor->Destroy(); // Destroy the other actor
}

// Event for when the projectile hits something
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Gets the other actors scale of the component in world space then multiplies it less than 1
		FVector scale = OtherComp->GetComponentScale();
		scale *= 0.8f;

		//Either it will destroy if it gets too small or it will split into smaller chunks
		if (scale.GetMin() < 0.99f)
			Explode(OtherActor);
		else
		{

			FActorSpawnParameters SpawnInfo;

			// Create spawn parameters
			ACube* baseActor = Cast<ACube>(OtherActor);
			UStaticMesh* newMesh = baseActor->GetStaticMeshComponent()->GetStaticMesh();
			FRotator Rotation = baseActor->GetActorRotation();
			FVector baseLocation = baseActor->GetActorLocation();
			FVector pieceLocation = FVector(0, 0, 0);
			FVector baseScale = baseActor->GetActorScale3D() * .25;

			// Destroy the other actor
			OtherActor->Destroy();

			// Split actor into seperate sections
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
				case 0:
					pieceLocation = FVector(baseLocation.X + baseScale.X, baseLocation.Y + baseScale.Y, baseLocation.Z);
					break;
				case 1:
					pieceLocation = FVector(baseLocation.X + baseScale.X, baseLocation.Y - baseScale.Y, baseLocation.Z);
					break;
				case 2:
					pieceLocation = FVector(baseLocation.X - baseScale.X, baseLocation.Y + baseScale.Y, baseLocation.Z);
					break;
				case 3:
					pieceLocation = FVector(baseLocation.X - baseScale.X, baseLocation.Y - baseScale.Y, baseLocation.Z);
					break;
				default:
					break;
				}

				// Spawn new actor with parameters
				ACube* newActor = GetWorld()->SpawnActor<ACube>(OtherActor->GetClass(), pieceLocation, Rotation, SpawnInfo);
				newActor->SetActorScale3D(baseScale);
				newActor->SetMobility(EComponentMobility::Movable);
				newActor->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				newActor->GetStaticMeshComponent()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
				newActor->GetStaticMeshComponent()->SetSimulatePhysics(true);
				newActor->GetStaticMeshComponent()->SetStaticMesh(newMesh);
				newActor->GetStaticMeshComponent()->SetMaterial(0, newActor->SmallMaterial);
			}
		}

		//Destroy Projectile at the end
		Destroy();
	}
}