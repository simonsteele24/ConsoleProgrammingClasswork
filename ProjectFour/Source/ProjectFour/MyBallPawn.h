// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBallPawn.generated.h"

UCLASS()
class PROJECTFOUR_API AMyBallPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBallPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Stats")
		float boostedJumpForce = 2000000;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		float currentJumpForce = 2000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float boostedSpeed = 3000000;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		float currentBallSpeed = 3000000;

	UPROPERTY(BlueprintReadWrite, Category = "States")
		bool jumping = false;
};
