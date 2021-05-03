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

	//Boosts 
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Stats")
		float boostedJumpForce = 2000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float boostedSpeed = 3000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Boost")
		float boostSpeedTime = 2.0f;

	//timer
	float timeSpeedBoosted = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Boost")
		float boostJumpTime = 2.0f;
	//timer
	float timeJumpBoosted = 0.0f;

	//Initial and Current Values
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float currentBallSpeed = 3000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float currentJumpForce = 2000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float startJumpForce = 3000000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		float startBallSpeed = 3000000;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stats")
		bool jumping = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		bool speedBoosted = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		bool jumpBoosted = false;


};
