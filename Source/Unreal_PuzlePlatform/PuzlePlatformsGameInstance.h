// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UPuzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	UPuzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

	virtual void Init();

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void JoinServer(const FString& IPaddr);
};
