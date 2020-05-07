// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StarChaserSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UStarChaserSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UStarChaserSaveGame* Create();
	static UStarChaserSaveGame* Load(FString SlotName);
	bool Save();
	void SerializeFromWorld(UWorld* World); //takes the current state of the world and put it into the Save Game Class
	void DeserializeFromWorld(UWorld* World); //take world from save game and put it into the world
	void SetHighestScore(int32 Score) { HighestScore = Score; }

	UFUNCTION(BlueprintCallable)
	FString GetSlotName() { return SlotName;}



	UFUNCTION(BlueprintCallable)
		void SetName(FString Name);

	UPROPERTY()
		FString SlotName;
	UPROPERTY()
		FString PlayerName = "Name";
	UPROPERTY()
		int32 HighestScore;
	UPROPERTY()
		TArray<FString> PlayerNames;
	UPROPERTY()
		TArray<int32> PlayerScores;
	UPROPERTY()
		int32 TotalStars;
	UPROPERTY()
		TArray<bool> BrightStarsActive;
	UPROPERTY()
		TArray<bool> FairiesActive;
	UPROPERTY()
		int32 MagnetUpgradeLevel = 1;
	UPROPERTY()
		float MagnetCooldown = 6.f;;
	UPROPERTY()
		int32 BootsUpgradeLevel = 1;
	UPROPERTY()
		float BootsCooldown = 6.f;
	UPROPERTY()
		bool bRunnerRunning = false;
	UPROPERTY()
		bool bNovaSkin = false;
};
