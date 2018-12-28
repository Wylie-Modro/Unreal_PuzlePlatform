// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

#include "UnrealString.h"

UPuzlePlatformsGameInstance::UPuzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) 
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
}

void UPuzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Init called"));
}

void UPuzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, TEXT("Hosting..."));

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
			UE_LOG(LogTemp, Warning, TEXT("Should be in new map"));
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("World* was a nullptr"));
		}
	}
}


void UPuzlePlatformsGameInstance::JoinServer(const FString& IPaddr)
{
	UEngine* Engine = GetEngine();
	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, FString::Printf(TEXT("Joining %s"), *IPaddr));
	}
}

