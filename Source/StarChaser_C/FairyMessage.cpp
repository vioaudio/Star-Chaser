// Fill out your copyright notice in the Description page of Project Settings.


#include "FairyMessage.h"
#include "StarChaserGameMode.h"


bool UFairyMessage::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!FairyMessage) return false;
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) FairyMessage->SetText(FText::FromString(GameMode->OutputMessage));
	return true;
}
