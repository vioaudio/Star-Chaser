// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMaster.h"
#include "Kismet/GameplayStatics.h"
#include "MenuCharacter.h"
#include "RunnerCharacter.h"

AUIMaster::AUIMaster()
{
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SavedSlotsGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("SavedSlotsGrid"));
	SavedSlotsGrid->SetupAttachment(GetRootComponent());

	GameOverMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameOverMenu"));
	GameOverMenu->SetupAttachment(GetRootComponent());

}

void AUIMaster::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Instance of UIMasterMade"));
	
}


void AUIMaster::DisplayGameOverMenu() 
{	
	UE_LOG(LogTemp, Warning, TEXT("Game Over Menu Displayed"));
	UGameOverMenu* Widget = Cast<UGameOverMenu>(GameOverMenu->GetUserWidgetObject());
	Widget->AddToViewport();
}

void AUIMaster::DisplaySavedSlotsGrid() 
{
	UE_LOG(LogTemp, Warning, TEXT("Saved Slots Grid Displayed"));
	USavedSlotsGrid* Widget = Cast<USavedSlotsGrid>(SavedSlotsGrid->GetUserWidgetObject());
		if (Widget) Widget->AddToViewport();

}




