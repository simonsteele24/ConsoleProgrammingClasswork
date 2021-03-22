// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
AGameManagerActor::AGameManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Checks if all conditions are right for it to broadcast the message
bool AGameManagerActor::CheckIfBroadcastIsRequired()
{
	// Get all cubes
	TArray<AActor*> result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), result);

	// Return if cube number is less than the required amount to change
	return result.Num() < NumBeforeChange;
}

// Broadcasts the new message to all deletegates that its time to switch materials
void AGameManagerActor::BroadcastNewMessage() 
{
	runningLowSignature.Broadcast();
}