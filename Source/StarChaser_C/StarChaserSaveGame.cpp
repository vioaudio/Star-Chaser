// Fill out your copyright notice in the Description page of Project Settings.


#include "StarChaserSaveGame.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"
#include "SaveGameIndex.h"
#include "StarChaserGameMode.h"

UStarChaserSaveGame* UStarChaserSaveGame::Create()
{
	UStarChaserSaveGame* NewSaveGame = Cast<UStarChaserSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr;

	USaveGameIndex* SaveGameIndex = USaveGameIndex::LoadIndex();
	SaveGameIndex->AddSaveGame(NewSaveGame);
	SaveGameIndex->SaveIndex();
	return NewSaveGame;
}

void UStarChaserSaveGame::DeserializeFromWorld(UWorld* World)
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(World->GetAuthGameMode());
	BrightStarsActive.SetNum(7);
	FairiesActive.SetNum(5);
	GameMode->SetHighestScore(HighestScore);
	GameMode->SetPlayerName(PlayerName);
	GameMode->SetPlayerNameArray(PlayerNames);
	GameMode->SetHighScoreArray(PlayerScores);
	GameMode->SetTotalStars(TotalStars);
	GameMode->SetBrightStars(BrightStarsActive);
	GameMode->SetFairies(FairiesActive);
	GameMode->SetMagnetCooldown(MagnetCooldown);
	GameMode->SetBootsCooldown(BootsCooldown);
	GameMode->SetMagnetUpgradeLevel(MagnetUpgradeLevel);
	GameMode->SetBootsUpgradeLevel(BootsUpgradeLevel);
	GameMode->SetRunnerState(bRunnerRunning);
	GameMode->bNovaSkin = bNovaSkin;
}

UStarChaserSaveGame* UStarChaserSaveGame::Load(FString SlotName)
{
	USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	UE_LOG(LogTemp, Warning, TEXT("Loaded: %s"), *SlotName);
	return  Cast<UStarChaserSaveGame>(LoadSaveGame);
}

bool UStarChaserSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0); 
}

void UStarChaserSaveGame::SerializeFromWorld(UWorld* World)
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(World->GetAuthGameMode());
	HighestScore = GameMode->HighestScore;
	PlayerName = GameMode->CurrentName;
	TotalStars = GameMode->TotalStars;
	MagnetCooldown = GameMode->MagnetCooldown;
	BootsCooldown = GameMode->BootsCooldown;
	MagnetUpgradeLevel = GameMode->MagnetUpgradeLevel;
	BootsUpgradeLevel = GameMode->BootsUpgradeLevel;
	bRunnerRunning = GameMode->bRunnerRunning;
	bNovaSkin = GameMode->bNovaSkin;
	BrightStarsActive.SetNum(7);
	FairiesActive.SetNum(5);
	PlayerScores.Empty();
	for (int i = 0; i < GameMode->PlayerScores.Num(); i++)
	{
		PlayerScores.Add(GameMode->PlayerScores[i]);
	}
	PlayerNames.Empty();
	for (int i = 0; i < GameMode->PlayerNames.Num(); i++)
	{
		PlayerNames.Add(GameMode->PlayerNames[i]);
	}

	//BrightStars & Fairies
	for (int i = 0; i < BrightStarsActive.Num(); i++)
	{
		BrightStarsActive[i] = false;
	}
	for (int i = 0; i < FairiesActive.Num(); i++)
	{
		FairiesActive[i] = false;
	}
	for (int i = 0; i < GameMode->BrightStarsActive.Num(); i++)
	{
		BrightStarsActive[i] = GameMode->BrightStarsActive[i];
	}
	for (int i = 0; i < GameMode->FairiesActive.Num(); i++)
	{
		FairiesActive[i] = GameMode->FairiesActive[i];
	}
}

void UStarChaserSaveGame::SetName(FString Name)
{
	PlayerName = Name;
	Save();
}

