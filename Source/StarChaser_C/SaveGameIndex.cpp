// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameIndex.h"
#include "Kismet/GameplayStatics.h"


const FString USaveGameIndex::SLOT_NAME = "SaveGameIndex";

USaveGameIndex* USaveGameIndex::LoadIndex()
{
	auto Index = Cast<USaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));
	if (!Index)
	{
		Index = Cast<USaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->SaveIndex();
	}
	return Index;
}

bool USaveGameIndex::SaveIndex()
{
	return UGameplayStatics::SaveGameToSlot(this, SLOT_NAME, 0);
}

void USaveGameIndex::AddSaveGame(UStarChaserSaveGame* SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}

void USaveGameIndex::ClearSlotNames()
{
	SlotNames.Empty();
}

void USaveGameIndex::ClearSlotName(FString SlotName)
{
	for (int i = 0; i < SlotNames.Num(); i++)
	{
		if (SlotNames[i] == SlotName)
		{
			SlotNames.RemoveAt(i, 1, true);
		}
	}
	SaveIndex();
}
