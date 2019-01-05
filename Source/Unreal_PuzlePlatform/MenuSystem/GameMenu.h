// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();

	UFUNCTION()
	void TeardownGameMenu();

protected:
	virtual bool Initialize() override;

private:
		UPROPERTY(meta = (BindWidget))
		class UButton* ResumeButton;

		UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

		UFUNCTION()
		void ReturnToMainMenu();
};
