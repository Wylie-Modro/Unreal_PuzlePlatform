// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize called"));
	bool SuperSuccessful = Super::Initialize();

	if (!SuperSuccessful) { return false; }
	UE_LOG(LogTemp, Warning, TEXT("SuperSuccessful true"));

	if (!ensure(HostButton != nullptr)) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(OpenJoinMenuButton != nullptr)) { return false; }
	OpenJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::GoBackToMainMenu);

	if (!ensure(JoinButton != nullptr)) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	UE_LOG(LogTemp, Warning, TEXT("All buttons true"));

	return true;
}

void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface != nullptr)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server"));

	MenuInterface->Host();
} 

void UMainMenu::JoinServer()
{


	if (!ensure(IPAddressField != nullptr)) { return; }
	const FString& IPAddress = IPAddressField->GetText().ToString();

	if (!ensure(MenuInterface != nullptr)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna join a server"));
	MenuInterface->Join(IPAddress);
} 

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher)
	{
		if (JoinMenu)
		{
			MenuSwitcher->SetActiveWidget(JoinMenu);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("JoinMenu is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MenuSwitcher is null"));
	}
}

void UMainMenu::GoBackToMainMenu()
{
	if (MenuSwitcher)
	{
		if (MainMenu)
		{
			MenuSwitcher->SetActiveWidget(MainMenu);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MainMenu is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MenuSwitcher is null"));
	}
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup() 
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(this->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UMainMenu::Teardown()
{
	RemoveFromViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;

			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = false;
		}
	}
}

/*
void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;

			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = false;

			Super::OnLevelRemovedFromWorld(InLevel, InWorld);
		}
	}
}
*/
