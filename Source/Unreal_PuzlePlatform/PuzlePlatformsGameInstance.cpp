// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UnrealString.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

UPuzlePlatformsGameInstance::UPuzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) 
{
	ConstructorHelpers::FClassFinder<UUserWidget> HostingMenuBP(TEXT("/Game/MenuSystem/WBP_HostUI"));
	if (HostingMenuBP.Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("Const Found Class: %s"), *HostingMenuBP.Class->GetName());

		HostingMenuClass = HostingMenuBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HostingMenuBP is a nullptr"));
	}



	ConstructorHelpers::FClassFinder<UUserWidget> GameMenuBP(TEXT("/Game/MenuSystem/WBP_GameUI"));
	if (GameMenuBP.Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("Const Found Class: %s"), *GameMenuBP.Class->GetName());

		GameMenuClass = GameMenuBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameMenuBP is a nullptr"));
	}

}

void UPuzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Init Found Class: %s"), *HostingMenuClass->GetName());
}

void UPuzlePlatformsGameInstance::Host()
{
	if (MainMenuInstance)
	{
		MainMenuInstance->Teardown();
	}

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


void UPuzlePlatformsGameInstance::Join(const FString& IPaddr)
{
	if (MainMenuInstance)
	{
		MainMenuInstance->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, FString::Printf(TEXT("Joining %s"), *IPaddr));

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(IPaddr, ETravelType::TRAVEL_Absolute);
		}
	}
}


void UPuzlePlatformsGameInstance::LoadMainMenu()
{
	if (HostingMenuClass)
	{
		MainMenuInstance = CreateWidget<UMainMenu>(this, HostingMenuClass);
		if (MainMenuInstance)
		{
			MainMenuInstance->Setup();
			MainMenuInstance->SetMenuInterface(this);
		}
	}
}

void UPuzlePlatformsGameInstance::LoadGameMenu()
{
	if (GameMenuClass)
	{
		GameMenuInstance = CreateWidget<UGameMenu>(this, GameMenuClass);
		if (GameMenuInstance)
		{
			GameMenuInstance->Setup();
			//GameMenuInstance->SetMenuInterface(this);
		}
	}
}

