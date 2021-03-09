// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "FPSBombActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Animation/AnimSequence.h"


AFPSCharacter::AFPSCharacter()
{
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->SetRelativeRotation(FRotator(2.0f, -15.0f, 5.0f));
	Mesh1PComponent->SetRelativeLocation(FVector(0, 0, -160.0f));

	// Create a gun mesh component
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");
}


void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("Special", IE_Released, this, &AFPSCharacter::SpawnSpecial);
	PlayerInputComponent->BindAction("SpawnBomb", IE_Pressed, this, &AFPSCharacter::SpawnBomb);

	PlayerInputComponent->BindAction("TimerDelegate", IE_Pressed, this, &AFPSCharacter::BeginDestructionSequence);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


}


void AFPSCharacter::Fire()
{
	// try and fire a projectile
	if (ProjectileClass)
	{
		// Grabs location from the mesh that must have a socket called "Muzzle" in his skeleton
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		// Use controller rotation which is our view direction in first person
		FRotator MuzzleRotation = GetControlRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}

void AFPSCharacter::SpawnBomb()
{

	AFPSBombActor* myBomb = GetWorld()->SpawnActor<AFPSBombActor>(BombClass,GetActorLocation(),GetActorRotation());
}


void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void AFPSCharacter::SpawnSpecial() 
{
	if (SpecialProjectileClass && bCanFireSpecial)
	{
		// Grabs location from the mesh that must have a socket called "Muzzle" in his skeleton
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		// Use controller rotation which is our view direction in first person
		FRotator MuzzleRotation = GetControlRotation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AFPSProjectile>(SpecialProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);

		bCanFireSpecial = false;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AFPSCharacter::StopCooldown, FireCooldown, false, FireCooldown);
	}
}


void AFPSCharacter::StopCooldown() 
{
	bCanFireSpecial = true;
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);
}


void AFPSCharacter::ActivateDestructionSequence() 
{
	if (ActorsToDestroy.Num() == 0) return;

	float randomScale = 0;

	for (int i = 0; i < ActorsToDestroy.Num(); i++) 
	{
		if (ActorsToDestroy[i] != nullptr) 
		{
			randomScale = FMath::RandRange(1.0f, 10.0f);
			ActorsToDestroy[i]->SetActorHiddenInGame(true);
			PlayExplosionEffect(randomScale, ActorsToDestroy[i]->GetActorLocation());
		}
	}
}


void AFPSCharacter::BeginDestructionSequence() 
{
	FTimerHandle timer;
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, FName("ActivateDestructionSequence"));

	UWorld* const world = GetWorld();

	if (world != nullptr) 
	{
		world->GetTimerManager().SetTimer(timer, timerDelegate, 3.0f, false);
	}
}


void AFPSCharacter::PlayExplosionEffect(float _Scale, const FVector & Location) 
{
	if (ExplosionEffect != nullptr) 
	{
		UParticleSystemComponent * ps = UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, Location);
		if (ps != nullptr) 
		{
			ps->SetWorldScale3D(FVector(_Scale));
		}
	}
}