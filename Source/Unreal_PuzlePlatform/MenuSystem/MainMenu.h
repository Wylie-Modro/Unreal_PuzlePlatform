// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString SessionName;
	uint32 CurrentPlayers;
	uint32 MaxPlayers;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer &ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerListOfData);

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	void Teardown();

	UFUNCTION()
	void SetSelectedIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	void UpdateChildern();

	TOptional<uint32> SelectedIndex;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreateSessionButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* OpenJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	//UPROPERTY(meta = (BindWidget))
	//class UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HostNameTextBox;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	IMenuInterface* MenuInterface;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void GoBackToMainMenu();

	UFUNCTION()
	void CallRefresh();
	
	UFUNCTION()
	void QuitGame();
};
