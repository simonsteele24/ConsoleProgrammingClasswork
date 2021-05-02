// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBallPawn.h"
#include "MyBallActor.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFOUR_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AMyPlayerController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyBallPawn* ballPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyBallActor* ballActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ballMeshComponent;
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void SetPlayerDataToController(AMyBallActor* myActor,AMyBallPawn* myPawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "PlayerBoost")
		void ActivateSpeedBoost();	

	UFUNCTION(BlueprintCallable, Category = "PlayerBoost")
		void ActivateJumpBoost();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PlayerBoostBools")
	bool speedBoost = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerBoostBools")
	bool jumpBoost = false;

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void Jump();
};
