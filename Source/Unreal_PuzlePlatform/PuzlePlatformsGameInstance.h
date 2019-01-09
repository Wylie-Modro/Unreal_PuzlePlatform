// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzlePlatformsGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UPuzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public: 
	UPuzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

	virtual void Init();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadGameMenu();

	UFUNCTION(Exec)
	void Host() override;
	
	UFUNCTION(Exec)
	void Join(const FString& IPaddr) override;


private: 
	TSubclassOf<class UUserWidget> HostingMenuClass;

	TSubclassOf<class UUserWidget> GameMenuClass;

	class UMainMenu* MainMenuInstance;

	class UGameMenu* GameMenuInstance;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	
};
