// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "GameFramework/Actor.h"
#include "JSONActor.generated.h"

UCLASS()
class FPSGAME_API AJSONActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJSONActor();

	FHttpModule* Http;
	FString url;
	FString windDirection;
	float temperature;
	float windSpeed;
	bool isDayTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Make the API request
	UFUNCTION()
	void HttpCall();
	UFUNCTION()
	void HttpCallURL(FString url);

	// Gets if it is day time
	UFUNCTION(BlueprintCallable) bool GetDayTime() { return isDayTime; }

	// Gets the wind direction
	UFUNCTION(BlueprintCallable) FString GetWindDirection() { return windDirection; }

	// Gets the wind speed
	UFUNCTION(BlueprintCallable) float GetWindSpeed() { return windSpeed; }

	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful);
	void OnResponseReceivedForeCast(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful);

	void ParseExample();
};
