// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::PlayerEffect(UObject* object,Boosts type)
{
	AMyBallPawn* ballPawn = Cast<AMyBallPawn>(object);
	if (ballPawn != NULL)
	{
		switch (type)
		{
		case Boosts::SPEED:
			if (!ballPawn->speedBoosted)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Speed"));
				ballPawn->currentBallSpeed = ballPawn->boostedSpeed;
			}
			
			break;

		case Boosts::JUMP:
			if (!ballPawn->jumpBoosted)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Jump"));
				ballPawn->currentJumpForce = ballPawn->boostedJumpForce;
			}
		
			break;

		case Boosts::CONTROL:
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Control"));
			break;
		}
	}
	
}
