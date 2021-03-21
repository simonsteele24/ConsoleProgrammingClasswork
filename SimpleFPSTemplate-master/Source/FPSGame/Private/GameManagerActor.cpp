// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Cube.h"

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

bool AGameManagerActor::CheckIfBroadcastIsRequired()
{
	TArray<AActor*> result;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), result);

	return result.Num() < NumBeforeChange;
}

void AGameManagerActor::BroadcastNewMessage() 
{
	runningLowSignature.Broadcast();
}