// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "PuzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("Player Joined! Now at %d players"), PlayerCount);

	if (PlayerCount >= 3)
	{

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) { return; }

		if (!(TimerHandler.IsValid()))
		{
			World->GetTimerManager().SetTimer(TimerHandler, this, &ALobbyGameMode::TimerExpired, 10.0f);
		}

	}
}

void ALobbyGameMode::TimerExpired()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Expired Bro"));

	auto GameInstance = Cast<UPuzlePlatformsGameInstance>(GetGameInstance());
	if (!ensure(GameInstance != nullptr)) { return; }
	GameInstance->StartMySession();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("Player Left. Now at %d players"), PlayerCount);
}

