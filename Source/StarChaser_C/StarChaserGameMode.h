// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Backdrop.h"
#include "Components/WidgetComponent.h"
#include "FairyMessage.h"
#include "HighScores.h"
#include "GameFramework/GameModeBase.h"
#include "GameOverMenu.h"
#include "MasterTile.h"
#include "StarChaserGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API AStarChaserGameMode : public AGameModeBase
{
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* BootsOnCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* BootsOffCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* MagnetOnCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* MagnetOffCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* StarPickUpCue;

	GENERATED_BODY()
public:
	AStarChaserGameMode();

	//Saved Data
	UFUNCTION()
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override; //Overrides from GameModeBase
	UFUNCTION(BlueprintCallable)
	void Save();
	UFUNCTION()
	void Load();
	UFUNCTION()
	void SaveAndQuit();
	UFUNCTION()
	void SortHighScores();


	FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentName;

	//Getters
	float GetInitialFloorTileCount() { return InitialFloorTileCount; }
	float GetForwardSpawnOffset() { return ForwardSpawnOffset; }
	float GetLaneOneOffset() { return LaneOneOffset; }
	float GetLaneTwoOffset() { return LaneTwoOffset; }
	float GetLaneThreeOffset() { return LaneThreeOffset; }

	UFUNCTION(BlueprintCallable)
		FString GetSlotName() { return SlotName; }
	UFUNCTION(BlueprintCallable)
		int32 GetHighestScore() { return HighestScore; }
	UFUNCTION(BlueprintCallable)
		int32 GetTotalStars() { return TotalStars; }
	UFUNCTION(BlueprintCallable)
		int32 GetCurrentStars() { return CurrentStars; }
	UFUNCTION(BlueprintCallable)
		int32 GetCurrentPoints() { return CurrentPoints; }
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetAllPlayerNames() { return AllPlayerNames; }
	UFUNCTION(BlueprintCallable)
		TArray<int32> GetAllPlayerScores() { return AllPlayerScores; }
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetPlayerNames() { return PlayerNames; }
	UFUNCTION(BlueprintCallable)
		TArray<int32> GetPlayerScores() { return PlayerScores; }
	UFUNCTION(BlueprintCallable)
		int32 BrightStarsCounter();
	UFUNCTION(BlueprintCallable)
		int32 FairiesCounter();
	UFUNCTION(BlueprintCallable)
		bool GetBrightStarActive(int32 index) { return BrightStarsActive[index];}
	UFUNCTION(BlueprintCallable)
		bool GetFairyActive(int32 index) { return FairiesActive[index]; }
	UFUNCTION(BlueprintCallable)
		bool GetGameFinishedState() { return bGameFinished; }


	//Setters
	UFUNCTION()
		void SetCurrentPoints(int32 Points) {CurrentPoints = Points;}
	UFUNCTION()
		void SetHighestScore(int32 Score) { HighestScore = Score; }
	UFUNCTION()
		void SetHighScoreArray(TArray<int32> PlayerScoresArray);
	UFUNCTION()
		void SetPlayerNameArray(TArray<FString> PlayerNamesArray);
	UFUNCTION()
		void SetPlayerName(FString Name) { CurrentName = Name; }
	UFUNCTION(BlueprintCallable)
		void SetTotalStars(int32 Stars) { TotalStars = Stars; }
	UFUNCTION(BlueprintCallable)
		void SetCurrentStars(int32 Stars) { CurrentStars = Stars; }
	UFUNCTION()
		void SetBrightStars(TArray<bool> BrightStarsArray);
	UFUNCTION()
		void SetFairies(TArray<bool> FairiesArray);
	UFUNCTION()
		void SetMessages();
	UFUNCTION(BlueprintCallable)
		void SetGameFinished(bool GameFinishedState) { bGameFinished = GameFinishedState; }
	
	UFUNCTION(BlueprintCallable)
		void SetBrightStarTrue(int32 Index) { BrightStarsActive[Index] = true; }
	UFUNCTION(BlueprintCallable)
		void SetFairyTrue(int32 Index) { FairiesActive[Index] = true; }
	UFUNCTION(BlueprintCallable)
		void SetMagnetCooldown(int32 NewCooldown) { MagnetCooldown = NewCooldown; }
	UFUNCTION(BlueprintCallable)
		void SetBootsCooldown(int32 NewCooldown) { BootsCooldown = NewCooldown; }
	UFUNCTION(BlueprintCallable)
		void SetMagnetUpgradeLevel(int32 NewLevel) { MagnetUpgradeLevel = NewLevel; }
	UFUNCTION(BlueprintCallable)
		void SetBootsUpgradeLevel(int32 NewLevel) { BootsUpgradeLevel = NewLevel; }
	UFUNCTION(BlueprintCallable)
		void SetRunnerState(bool RunnerState) { bRunnerRunning = RunnerState; }
	UFUNCTION()
		void SetScoresAndNames();
	UFUNCTION()
		void CollectiblesArraySetup(); 
	UFUNCTION()
		void SetAudio();

	//AUDIO
	UFUNCTION(BlueprintCallable)
		void FadeInMenuMusic() { MenuMusic->SetVolumeMultiplier(1.f), MenuMusic->Play(), MenuMusic->FadeIn(2.f); }
	UFUNCTION(BlueprintCallable)
		void FadeOutMenuMusic() { MenuMusic->FadeOut(1.f, 0); }
	UFUNCTION(BlueprintCallable)
		void FadeInGameMusic() { InGameMusic->SetVolumeMultiplier(1.f), InGameMusic->Play(), InGameMusic->FadeIn(2.f); }
	UFUNCTION(BlueprintCallable)
		void FadeOutGameMusic() { InGameMusic->FadeOut(2.f, 0); }

	//GameData
	int32 CurrentPoints;
	int32 HighestScore;
	int32 TotalStars;	
	int32 CurrentStars;
	float MagnetCooldown = 6.f;
	float BootsCooldown = 6.f;

	TArray<FString> PlayerNames;
	TArray<int32> PlayerScores;
	TArray<FString> AllPlayerNames;
	TArray<int32> AllPlayerScores;
	TArray<bool> BrightStarsActive;
	TArray<bool> FairiesActive;
	TArray<FString> Messages;
	FString OutputMessage = "Thank You";
	bool bGameFinished = false;
	bool bHasDied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bRunnerRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMainMenuMusicOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MagnetUpgradeLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BootsUpgradeLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bNovaSkin = false;

	//UI
		void DisplayGameOverMenu();
		void DisplayHighScores();
		void DisplayFairyMessage();

	//Cloud Platform
		bool bCanSpawnPlatform = false;
		bool bCanSpawnObstacle = true;

	//Sound 
		void PlayBootsOn() { BootsOnAudioComponent->Play(); }
		void PlayBootsOff() { BootsOffAudioComponent->Play(); }
		void PlayMagnetOn() { MagnetOnAudioComponent->Play(); }
		void PlayMagnetOff() { MagnetOffAudioComponent->Play(); }
		void PlayStarPickUp() { StarPickUpAudioComponent->Play(); }

protected:
	void BeginPlay() override;

private:
	//Configuration
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMasterTile> InitialFloorClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UHighScores> HighScoresClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UBackdrop> BackDropClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UFairyMessage> FairyMessageClass;

	
	private:
		//Sound
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* BootsOnAudioComponent;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* BootsOffAudioComponent;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* MagnetOnAudioComponent;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* MagnetOffAudioComponent;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* StarPickUpAudioComponent;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* MenuMusic;
	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* InGameMusic;

	
	UFUNCTION()
	void SpawnInitialFloor();

	UPROPERTY(EditAnywhere)
		float ForwardSpawnOffset = -500.1f;
	UPROPERTY(EditAnywhere)
		float InitialFloorTileCount = 20.f;
	UPROPERTY(EditAnywhere)
		float LaneOneOffset = 32.6f;
	UPROPERTY(EditAnywhere)
		float LaneTwoOffset = 0.f;
	UPROPERTY(EditAnywhere)
		float LaneThreeOffset = -32.6f;


	FString Message1 = "\" You Got This \"";
	FString Message2 = "\" Your Light Guides You \"";
	FString Message3 = "\" You Shine Bright \"";
	FString Message4 = "\" The Stars Join You Tonight \"";
	FString Message5 = "\" Love is Forever \"";
	FString Message6 = "\" I believe in You \"";
	FString Message7 = "\" Fly Me to the Moon \"";
	FString Message8 = "\" The Sky is Your Canvas \"";

	//UI	
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* GameOverMenu;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* HighScores;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* Backdrop;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* FairyMessage;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
};
