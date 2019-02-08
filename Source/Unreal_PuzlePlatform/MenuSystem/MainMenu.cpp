// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "UObject/ConstructorHelpers.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBP(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowBP.Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("Const Found Class: %s"), *ServerRowBP.Class->GetName());

		ServerRowClass = ServerRowBP.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ServerRowBP is a nullptr"));
	}
}

bool UMainMenu::Initialize()
{
	bool SuperSuccessful = Super::Initialize();

	if (!SuperSuccessful) { return false; }
	UE_LOG(LogTemp, Warning, TEXT("SuperSuccessful true"));

	if (!ensure(HostButton != nullptr)) { return false; }
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(OpenJoinMenuButton != nullptr)) { return false; }
	OpenJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(QuitGameButton!= nullptr)) { return false; }
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	if (!ensure(CancelButton != nullptr)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::GoBackToMainMenu);

	if (!ensure(JoinButton != nullptr)) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(RefreshButton != nullptr)) { return false; }
	RefreshButton->OnClicked.AddDynamic(this, &UMainMenu::CallRefresh);

	return true;
}

void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface != nullptr)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server"));

	MenuInterface->Host();
} 

void UMainMenu::SetServerList(TArray<FString> ServerListNames)
{
	if (ServerRowClass)
	{
		UWorld* World = this->GetWorld();
		if (!ensure(World != nullptr)) { return; }

		ServerList->ClearChildren();

		int RowIndex = 0;
		for (const FString& ServerListName : ServerListNames) {

			UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
			if (!ensure(Row != nullptr)) { return; }

			if (!ensure(Row->ServerName != nullptr)) { return; }
			Row->ServerName->SetText(FText::FromString(ServerListName));
			Row->Setup(this, RowIndex);
			++RowIndex;

			ServerList->AddChild(Row);
		}
	}
}

void UMainMenu::CallRefresh()
{
	if (!ensure(MenuInterface != nullptr)) { return; }
	MenuInterface->RefreshServerList();
}

void UMainMenu::SetSelectedIndex(uint32 Index)
{
	SelectedIndex = Index;

	UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), Index);
}

void UMainMenu::JoinServer()
{

//	if (!ensure(IPAddressField != nullptr)) { return; }
//	const FString& IPAddress = IPAddressField->GetText().ToString();

//	if (!ensure(MenuInterface != nullptr)) { return; }
//	UE_LOG(LogTemp, Warning, TEXT("I'm gonna join a server"));
//	MenuInterface->Join(IPAddress);

	if (SelectedIndex.IsSet())
	{
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No session selected"));
	}
} 

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher)
	{
		if (JoinMenu)
		{
			MenuSwitcher->SetActiveWidget(JoinMenu);

			if (MenuInterface)
			{
				MenuInterface->RefreshServerList();
			}
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


void UMainMenu::QuitGame()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (!ensure(PlayerController != nullptr)) { return; }
	PlayerController->ConsoleCommand(FString("Quit"));
}

