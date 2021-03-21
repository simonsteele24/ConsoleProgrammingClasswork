// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class FPSGAME_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
