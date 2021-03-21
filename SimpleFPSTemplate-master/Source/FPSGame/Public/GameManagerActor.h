// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManagerActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FRunningLow)

UCLASS()
class FPSGAME_API AGameManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/* Integers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int NumBeforeChange = 60;

	/* Functions */
	UFUNCTION(BlueprintCallable) bool CheckIfBroadcastIsRequired();
	UFUNCTION(BlueprintCallable) void BroadcastNewMessage();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Event Handlers */
	FRunningLow runningLowSignature;

};
