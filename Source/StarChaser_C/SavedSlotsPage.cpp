// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedSlotsPage.h"
#include "StarChaserSaveGame.h"


// Sets default values
ASavedSlotsPage::ASavedSlotsPage()
{
}

void ASavedSlotsPage::AddSaveSlot()
{
	UStarChaserSaveGame::Create();
	RefreshSlots();
}

// Called when the game starts or when spawned
void ASavedSlotsPage::BeginPlay()
{
	Super::BeginPlay();
}

void ASavedSlotsPage::RefreshSlots()
{
}


