
#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MenuCharacter.h"
#include "NameEntry.h"
#include "RunnerCharacter.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SavedSlotsGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("SavedSlotsGrid"));
	SavedSlotsGrid->SetupAttachment(GetRootComponent()); 

	NameEntry = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameEntry"));
	NameEntry->SetupAttachment(GetRootComponent());
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void AMainMenuGameMode::DisplaySavedSlotsGrid()
{
	USavedSlotsGrid* Widget = Cast<USavedSlotsGrid>(SavedSlotsGrid->GetUserWidgetObject());
	if (Widget) Widget->AddToViewport();
}

void AMainMenuGameMode::RemoveSavedSlotsGrid()
{
	USavedSlotsGrid* Widget = Cast<USavedSlotsGrid>(SavedSlotsGrid->GetUserWidgetObject());
	if (Widget) Widget->RemoveFromViewport();
}

void AMainMenuGameMode::DisplayNameEntry()
{
	UNameEntry* Widget = Cast<UNameEntry>(NameEntry->GetUserWidgetObject());
	if (Widget) Widget->AddToViewport();
}

void AMainMenuGameMode::FadeOutMenuMusic()
{
	FindComponentByClass<UAudioComponent>()->FadeOut(1.0f, 0);
}





