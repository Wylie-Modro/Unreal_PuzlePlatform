// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UNREAL_PUZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public: 
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 10; // cm/s

	UPROPERTY(EditAnywhere, Category = "Target", Meta = (MakeEditWidget = true))
	FVector TargetPoint;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private: 
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	int ActivePlatformsCount = 1;
};
