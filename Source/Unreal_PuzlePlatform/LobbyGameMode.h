// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unreal_PuzlePlatformGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API ALobbyGameMode : public AUnreal_PuzlePlatformGameMode
{
	GENERATED_BODY()


	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual void Logout(AController* Exiting) override;

	void TimerExpired();

	int PlayerCount = 0;

	FTimerHandle TimerHandler;
};
