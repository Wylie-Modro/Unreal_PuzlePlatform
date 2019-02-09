// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_PUZLEPLATFORM_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	void Setup(class UMainMenu* pParent, uint32 pIndex);

	UPROPERTY(BlueprintReadOnly)
	bool isSelected = false;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerRowButton;

private:
	UFUNCTION()
	void OnClickedRow();

	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;
};
