// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "UnrealString.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"


const FName SESSION_NAME = TEXT("My Session Game");


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
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Init Found OSS: %s"), *OSS->GetSubsystemName().ToString());
		SessionInterface = OSS->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Init Got SessionInterface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzlePlatformsGameInstance::OnDestroySessionComplete);
		} 
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SessionInterface is not valid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Init NOT Found OSS"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Init Found Class: %s"), *HostingMenuClass->GetName());
}

// Old Host Method without steam and only in local network
/*
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
*/

void UPuzlePlatformsGameInstance::Host()
{
		
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Session to be destroyed"));
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SessionInterface.IsValid() = FALSE"));
	}

}

void UPuzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Error, TEXT("No bogerts here"));

	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Could Not Create Session"));
		return;
	}

	if (MainMenuInstance)
	{
		MainMenuInstance->Teardown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) { return; }
	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, TEXT("Hosting..."));
		UWorld* World = GetWorld();
		if (World)
		{
			if (!ensure(World != nullptr)) { return; }
			
			UE_LOG(LogTemp, Warning, TEXT("Actor count: %d"), World->GetActorCount());
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
			UE_LOG(LogTemp, Warning, TEXT("Should be in new map"));
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("World* was a nullptr"));
		}
	}
		UE_LOG(LogTemp, Error, TEXT("Poo Bear"));
}

void UPuzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Will create session"));
		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session was destroyed, now creating new session"));
		// because we did want to actually create the session
		CreateSession();
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

