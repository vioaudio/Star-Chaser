// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedSlotsGrid.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuGameMode.h"
#include "SaveGameIndex.h"
#include "Styling/SlateColor.h"
#include "StarChaserSaveGame.h"

bool USavedSlotsGrid::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!AddSlot) return false;
	AddSlot->OnClicked.AddDynamic(this, &USavedSlotsGrid::CreateSaveGame);
	RemoveSlotsButton->OnClicked.AddDynamic(this, &USavedSlotsGrid::RemoveSlots);
	RefreshSlots();
	RemoveSlotsButton->SetRenderOpacity(1);
	auto SlotNames = USaveGameIndex::LoadIndex()->GetSlotNames();
	
	return true;
	
}

void USavedSlotsGrid::AddSavedSlot(int32 SavedSlotIndex, FString SavedSlotName)
{
	UStarChaserSaveGame* SavedGame = UStarChaserSaveGame::Load(SavedSlotName);
	if (!SavedSlotsGrid) return;

	if (!DeleteMode)
	{
		USaveSlot* SaveWidget = CreateWidget<USaveSlot>(GetWorld(), SaveSlotClass);
		if (!SaveWidget) return;
		SaveWidget->SetSaveSlotName(SavedSlotName, SavedGame->PlayerName);

		USizeBox* SaveSlotContainer = Cast<USizeBox>(SavedSlotsGrid->GetChildAt(SavedSlotIndex));
		if (!SaveSlotContainer) return;
		SaveSlotContainer->AddChild(SaveWidget);
	}

	if (DeleteMode)
	{
		UDeleteSlot* DeleteWidget = CreateWidget<UDeleteSlot>(GetWorld(), DeleteSlotClass);
		if (!DeleteWidget) return;
		DeleteWidget->SetSaveSlotName(SavedSlotName, SavedGame->PlayerName);
		DeleteWidget->Index = SavedSlotIndex;

		USizeBox* SaveSlotContainer = Cast<USizeBox>(SavedSlotsGrid->GetChildAt(SavedSlotIndex));
		if (!SaveSlotContainer) return;
		SaveSlotContainer->AddChild(DeleteWidget);
	}


}

void USavedSlotsGrid::CreateSaveGame()
{
	auto SlotNames = USaveGameIndex::LoadIndex()->GetSlotNames();
	UE_LOG(LogTemp, Warning, TEXT("Number of Slot Names:, %d"), SlotNames.Num());
	if (SlotNames.Num() >= 3)
	{
		
	}
	else
	{
		UStarChaserSaveGame* NewSaveGame = UStarChaserSaveGame::Create();
		NewSaveGame->Save();
		SlotName = NewSaveGame->SlotName;
		AMainMenuGameMode* GameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->SetSlotName(SlotName);
		RefreshSlots();
	}
}


void USavedSlotsGrid::ClearSlots()
{
	for (int32 i = 0; i < (SavedSlotsGrid->GetChildrenCount()); i++)
	{
		USizeBox* SaveSlotContainer = Cast<USizeBox>(SavedSlotsGrid->GetChildAt(i));
		if (!SaveSlotContainer) continue;

		SaveSlotContainer->ClearChildren();
	}
}

void USavedSlotsGrid::DeleteSlot()
{
}

void USavedSlotsGrid::RemoveSlots()
{
	DeleteMode = true;
	RefreshSlots();
}

int32 USavedSlotsGrid::GetNumberOfSlots() const
{
	return SavedSlotsGrid->GetChildrenCount();
}

void USavedSlotsGrid::RefreshSlots()
{
	ClearSlots();

	auto SlotNames = USaveGameIndex::LoadIndex()->GetSlotNames();
	if (SlotNames.Num() >= 3)
	{
		
	}
	if (SlotNames.Num() < 1) return;
	for (int32 i = 0; i < GetNumberOfSlots() && i < SlotNames.Num(); ++i)
	{
		AddSavedSlot(i, SlotNames[i]);
	}
}