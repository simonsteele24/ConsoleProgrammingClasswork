// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Materials/Material.h"
#include "Cube.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FRunningLow)

UCLASS()
class FPSGAME_API ACube : public AStaticMeshActor
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* SmallMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* DangerMaterial;

    UFUNCTION()
    void ChangeToDanger();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
protected:
    UPROPERTY() class AFPSGameModeBase* GameMode;
};
