// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProjectile.h"
#include "FPSProjectileSpecial.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSProjectileSpecial : public AFPSProjectile
{
	GENERATED_BODY()
	
public:
	AFPSProjectileSpecial();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ExplosionRadius = 200.0f;

	/** called when projectile hits something */
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
