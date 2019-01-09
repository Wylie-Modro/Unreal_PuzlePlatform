// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	void Teardown();

protected:
	virtual bool Initialize() override;

private:
		UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;
	
		UPROPERTY(meta = (BindWidget))
		class UButton* OpenJoinMenuButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* QuitGameButton;

		UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

		UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

		UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

		UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;

		IMenuInterface* MenuInterface;

		UFUNCTION()
		void HostServer();

		UFUNCTION()
		void JoinServer();

		UFUNCTION()
		void OpenJoinMenu();

		UFUNCTION()
		void GoBackToMainMenu();

		UFUNCTION()
		void QuitGame();

};
