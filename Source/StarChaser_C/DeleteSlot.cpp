// Fill out your copyright notice in the Description page of Project Settings.


#include "DeleteSlot.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameIndex.h"
#include "SavedSlotsGrid.h"
#include "StarChaserSaveGame.h"


void UDeleteSlot::SetSaveSlotName(FString NewSaveSlotName, FString PlayerName)
{
	SaveSlotName = NewSaveSlotName;

	Name->SetText(FText::FromString(PlayerName));
	DeleteSaveSlotButton->OnClicked.AddDynamic(this, &UDeleteSlot::ButtonClicked);
}

void UDeleteSlot::ButtonClicked()
{
	if (bClickable)
	{
		USaveGameIndex* SaveGameIndex = USaveGameIndex::LoadIndex();
		SaveGameIndex->ClearSlotName(SaveSlotName);
		Name->SetText(FText::FromString(TEXT("Deleted")));
		bClickable = false;
		UGameplayStatics::DeleteGameInSlot(SaveSlotName, 0);
		SaveGameIndex->SaveIndex();
	}
}