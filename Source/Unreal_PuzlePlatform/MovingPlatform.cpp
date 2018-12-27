// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetPoint);
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ActivePlatformsCount > 0)
	{
		FVector Location = GetActorLocation();
		float IntendedPathLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float CurrentPathLength = (Location - GlobalStartLocation).Size();
		if (IntendedPathLength <= CurrentPathLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation ;
			GlobalTargetLocation = Swap;
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}


void AMovingPlatform::AddActiveTrigger() 
{
	ActivePlatformsCount++;
}

void AMovingPlatform::RemoveActiveTrigger() 
{
	if (ActivePlatformsCount > 0)
	{
		ActivePlatformsCount--;
	}
}
