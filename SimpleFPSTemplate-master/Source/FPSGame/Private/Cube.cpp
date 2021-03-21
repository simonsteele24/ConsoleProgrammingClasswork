// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "FPSGameModeBase.h"
#include "GameManagerActor.h"
#include "Kismet/GameplayStatics.h"

void ACube::ChangeToDanger() 
{
	GetStaticMeshComponent()->SetMaterial(0, DangerMaterial);
}

void ACube::BeginPlay() 
{
	TArray<AActor*> result;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameManagerActor::StaticClass(), result);

	GameMode = Cast<AGameManagerActor>(result[0]);
	GameMode->runningLowSignature.AddUObject(this, &ACube::ChangeToDanger);
}