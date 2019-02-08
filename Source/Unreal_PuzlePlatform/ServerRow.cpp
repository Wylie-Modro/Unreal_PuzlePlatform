// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"

#include "MenuSystem/MainMenu.h"

void UServerRow::Setup(UMainMenu* pParent, uint32 pIndex)
{
	Parent = pParent;
	Index = pIndex;

	if (!ensure(ServerRowButton != nullptr)) { return; }
	ServerRowButton->OnClicked.AddDynamic(this, &UServerRow::OnClickedRow);
}

void UServerRow::OnClickedRow()
{
	Parent->SetSelectedIndex(Index);
}

