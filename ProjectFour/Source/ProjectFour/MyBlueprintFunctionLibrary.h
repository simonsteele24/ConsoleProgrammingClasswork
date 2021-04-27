// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBallPawn.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UENUM(BlueprintType, Category = "Effects")
enum Boosts
{
	SPEED,
	JUMP,
	CONTROL,

};


UCLASS()
class PROJECTFOUR_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	UFUNCTION(BlueprintCallable, Category = "PowerUp")
		static void PlayerEffect(UObject* object,Boosts type);

};
