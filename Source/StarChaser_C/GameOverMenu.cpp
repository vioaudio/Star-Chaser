// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenu.h"
#include "HighScores.h"
#include "Kismet/GameplayStatics.h"
#include "StarChaserGameMode.h"
#include "RunnerCharacter.h"

bool UGameOverMenu::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!DreamOn) return false;
	if (!HighScores) return false;
	if (!Menu) return false;
	if (!StarShop) return false;

	DreamOn->OnClicked.AddDynamic(this, &UGameOverMenu::Restart);
	HighScores->OnClicked.AddDynamic(this, &UGameOverMenu::ShowHighScores);
	Menu->OnClicked.AddDynamic(this, &UGameOverMenu::ShowMenu);
	StarShop->OnClicked.AddDynamic(this, &UGameOverMenu::Shop);
	return true;
}

void UGameOverMenu::Restart()
{
	UE_LOG(LogTemp, Warning, TEXT("Restart"));
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->CurrentPoints = 0;
	GameMode->CurrentStars = 0;
	GameMode->SetRunnerState(true);
	GameMode->Save();
	RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StarChaserLevel1"), true, "SlotName=" + GameMode->SlotName);
}

void UGameOverMenu::ShowHighScores()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetRunnerState(false);
	GameMode->Save();
	GameMode->DisplayHighScores();
	GameMode->FadeOutGameMusic();
	GameMode->FadeInMenuMusic();
	GameMode->bMainMenuMusicOn = true;
}

void UGameOverMenu::ShowMenu()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetRunnerState(false);
}

void UGameOverMenu::Shop()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetRunnerState(false);
	GameMode->Save();
	GameMode->FadeOutGameMusic();
	GameMode->FadeInMenuMusic();
	GameMode->bMainMenuMusicOn = true;
}
