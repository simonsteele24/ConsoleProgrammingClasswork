// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectileSpecial.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"


AFPSProjectileSpecial::AFPSProjectileSpecial() 
{
}


void AFPSProjectileSpecial::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	AStaticMeshActor* baseActor = Cast<AStaticMeshActor>(OtherActor);

	if (baseActor != nullptr) 
	{
		TArray<AActor*> result;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), result);

		for (int i = 0; i < result.Num(); i++) 
		{
			if (FVector::Distance(baseActor->GetActorLocation(), result[i]->GetActorLocation()) <= ExplosionRadius) 
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, explosionTemplate, result[i]->GetActorLocation());
				result[i]->Destroy();
			}
		}

		UGameplayStatics::SpawnEmitterAtLocation(this, explosionTemplate, GetActorLocation());
		OtherActor->Destroy();
		Destroy();
	}

}