// Fill out your copyright notice in the Description page of Project Settings.


#include "JSONActor.h"

// Sets default values
AJSONActor::AJSONActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJSONActor::BeginPlay()
{
	Super::BeginPlay();
    ParseExample();
}

// Called every frame
void AJSONActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJSONActor::ParseExample()
{
    const FString JsonFilePath = FPaths::ProjectContentDir() + "/JSONFiles/ChamplainForecast.json";
    FString JsonString; //The json file to string

    FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

    //Displaying the json in a string format inside the output log
    GLog->Log("Json String:");
    GLog->Log(JsonString);

    //https://api.weather.gov/points/44.4731,-73.2041
    FString JsonRaw = "{ \"properties\": \"updated\" }";
    TSharedPtr<FJsonObject> JsonParsed;
    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
    if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
    {
        //The person "object" that is retrieved from the given json file
        TSharedPtr<FJsonObject> PersonObject = JsonParsed->GetObjectField("properties");
        //Getting various properties
        GLog->Log("ITWORKS! updated:" + PersonObject->GetStringField("updated"));
        GLog->Log("forecastGenerator:" + PersonObject->GetStringField("forecastGenerator"));
        GLog->Log("ITWORKS! generatedAt:" + PersonObject->GetStringField("generatedAt"));
        GLog->Log("updateTime:" + PersonObject->GetStringField("updateTime"));
        GLog->Log("validTimes:" + PersonObject->GetStringField("validTimes"));
/*
 "updated": "2021-03-10T17:15:16+00:00",
        "units": "us",
        "forecastGenerator": "BaselineForecastGenerator",
        "generatedAt": "2021-03-10T18:54:10+00:00",
        "updateTime": "2021-03-10T17:15:16+00:00",
        "validTimes": "2021-03-10T11:00:00+00:00/P7DT14H",
*/
     //   FString ExampleString = JsonParsed->GetStringField((JsonRaw));
       // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, ExampleString);
      //  JsonParsed->GetStringField(JsonRaw);
    }
}
