// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"

#include "GameFramework/GameModeBase.h" 
#include "Components/Button.h"

bool UGameMenu::Initialize()
{
	bool SuperSuccessful = Super::Initialize();

	if (!SuperSuccessful) { return false; }
	UE_LOG(LogTemp, Warning, TEXT("SuperSuccessful true"));

	if (!ensure(ResumeButton != nullptr)) { return false; }
	ResumeButton->OnClicked.AddDynamic(this, &UGameMenu::TeardownGameMenu);

	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UGameMenu::ReturnToMainMenu);

	UE_LOG(LogTemp, Warning, TEXT("Resume Button true"));

	return true;
}

void UGameMenu::Setup() 
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

void UGameMenu::TeardownGameMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Teardown from cancel button Called"))

	RemoveFromViewport();
	UE_LOG(LogTemp, Warning, TEXT("RemoveFromViewport(); from cancel button Called"))

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

void UGameMenu::ReturnToMainMenu()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (!ensure(PlayerController != nullptr)) { return; }
	UWorld* World = PlayerController->GetWorld();

	if (!ensure(World!= nullptr)) { return; }

	if (World->IsServer())
	{
		AGameModeBase* GameMode = World->GetAuthGameMode<AGameModeBase>();
		if (GameMode)
		{
			GameMode->ReturnToMainMenuHost();
		}
	}
	else
	{
		PlayerController->ClientReturnToMainMenu("Back to Main Menu");
	}
}
