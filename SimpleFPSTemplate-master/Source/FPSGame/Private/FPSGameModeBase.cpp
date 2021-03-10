// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Cube.h"

// Called when the game starts or when spawned
void AFPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPSGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckIfBroadcastIsRequired()) 
	{
		runningLowSignature.Broadcast();
	}
}


bool AFPSGameModeBase::CheckIfBroadcastIsRequired() 
{
	TArray<AActor*> result;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), result);

	return result.Num() < NumBeforeChange;
}