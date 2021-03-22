// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "LowLevelFire.h"

// Sets default values
ALowLevelFire::ALowLevelFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALowLevelFire::BeginPlay()
{
	// Get and set the game mode actor
	TArray<AActor*> result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameManagerActor::StaticClass(), result);
	GameMode = Cast<AGameManagerActor>(result[0]);

	// Add object as a listener to the multicast delegate
	GameMode->runningLowSignature.AddUObject(this, &ALowLevelFire::ChangeVisibilityBasedOnCubes);
	
}



// Called every frame
void ALowLevelFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALowLevelFire::ChangeVisibilityBasedOnCubes() 
{
	SetActorHiddenInGame(false);
}