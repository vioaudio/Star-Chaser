// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlot.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuGameMode.h"
#include "StarChaserGameMode.h"
#include "TimerManager.h"


void USaveSlot::SetSaveSlotName(FString NewSaveSlotName, FString PlayerName) //Called From SavedSlotsGrid.cpp AddSavedSlot
{
	SaveSlotName = NewSaveSlotName; 
	
	Name->SetText(FText::FromString(PlayerName));
	OpenSaveSlotButton->OnClicked.AddDynamic(this, &USaveSlot::ButtonClicked);
}

void USaveSlot::ButtonClicked()
{
	AMainMenuGameMode* MenuGameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
	if (MenuGameMode) MenuGameMode->FadeOutMenuMusic();
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode) GameMode->FadeOutMenuMusic();

	GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &USaveSlot::OpenLevel, 1.f, false);
}

void USaveSlot::OpenLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StarChaserLevel1"), true, "SlotName=" + SaveSlotName);
}
