// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuGameMode.h"
#include "SaveGameIndex.h"
#include "SavedSlotsGrid.h"
#include "StarChaserSaveGame.h"

AMenuCharacter::AMenuCharacter()
{
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SavedSlotsGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("SavedSlotsGrid"));
	SavedSlotsGrid->SetupAttachment(GetRootComponent());

}

void AMenuCharacter::BeginPlay()
{
	Super::BeginPlay();
	//AMainMenuGameMode* GameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
	//GameMode->DisplaySavedSlotsGrid();
}

USavedSlotsGrid* AMenuCharacter::GetSavedSlotsGrid() const
{
	return Cast<USavedSlotsGrid>(SavedSlotsGrid->GetUserWidgetObject());
}

void AMenuCharacter::RefreshSlots()
{
	if (!GetSavedSlotsGrid()) return;

	GetSavedSlotsGrid()->ClearSlots();

	auto SlotNames = USaveGameIndex::LoadIndex()->GetSlotNames();
	for (int32 i = 0; i < GetSavedSlotsGrid()->GetNumberOfSlots(); ++i)
	{
		GetSavedSlotsGrid()->AddSavedSlot(i, SlotNames[i]);
	}
}

// Called to bind functionality to input
void AMenuCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Save", IE_Pressed, this, &AMenuCharacter::Save);
	PlayerInputComponent->BindAction("Start", IE_Released, this, &AMenuCharacter::StartGame);
}

void AMenuCharacter::Save()
{
	SavedGame = UStarChaserSaveGame::Create();
	SavedGame->Save();
	SlotName = SavedGame->SlotName;
	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s Has Been Created"), *SlotName);
}

void AMenuCharacter::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StarChaserLevel1"), true, "SlotName=" + SlotName);
}



