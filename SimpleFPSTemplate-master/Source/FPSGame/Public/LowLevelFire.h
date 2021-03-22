// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LowLevelFire.generated.h"

DECLARE_MULTICAST_DELEGATE(FRunningLow)

UCLASS()
class FPSGAME_API ALowLevelFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALowLevelFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChangeVisibilityBasedOnCubes();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Game Managers */
	UPROPERTY() class AGameManagerActor* GameMode;
};
