// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "StarChaserGameMode.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameOverMenu.h"
#include "MasterTile.h"
#include "Kismet/GameplayStatics.h"
#include "StarChaserSaveGame.h"
#include "SaveGameIndex.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"

AStarChaserGameMode::AStarChaserGameMode()
{
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GameOverMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameOverMenu"));
	GameOverMenu->SetupAttachment(GetRootComponent());

	MenuMusic = CreateDefaultSubobject<UAudioComponent>(TEXT("MenuMusic"));
	MenuMusic->SetupAttachment(Root);
	InGameMusic = CreateDefaultSubobject<UAudioComponent>(TEXT("InGameMusic"));
	InGameMusic->SetupAttachment(Root);

	//AUDIO
	static ConstructorHelpers::FObjectFinder<USoundCue> BootsOnSoundObject(TEXT("SoundCue'/Game/Audio/Cues/BootsOnCue.BootsOnCue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BootsOffSoundObject(TEXT("SoundCue'/Game/Audio/Cues/BootsOffCue.BootsOffCue'"));
	if (BootsOnSoundObject.Succeeded() && BootsOffSoundObject.Succeeded())
	{
		BootsOnCue = BootsOnSoundObject.Object;
		BootsOffCue = BootsOffSoundObject.Object;

		BootsOnAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BootsOnAudioComponent"));
		BootsOnAudioComponent->SetupAttachment(Root);

		BootsOffAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BootsOffAudioComponent"));
		BootsOffAudioComponent->SetupAttachment(Root);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> MagnetOnSoundObject(TEXT("SoundCue'/Game/Audio/Cues/MagnetOnCue.MagnetOnCue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MagnetOffSoundObject(TEXT("SoundCue'/Game/Audio/Cues/MagnetOffCue.MagnetOffCue'"));
	if (MagnetOnSoundObject.Succeeded() && MagnetOffSoundObject.Succeeded())
	{
		MagnetOnCue = MagnetOnSoundObject.Object;
		MagnetOffCue = MagnetOffSoundObject.Object;

		MagnetOnAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MagnetOnAudioComponent"));
		MagnetOnAudioComponent->SetupAttachment(Root);

		MagnetOffAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MagnetOffAudioComponent"));
		MagnetOffAudioComponent->SetupAttachment(Root);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> StarPickUpSoundObject(TEXT("SoundCue'/Game/Audio/Cues/StarPickUpCue.StarPickUpCue'"));
	if (StarPickUpSoundObject.Succeeded())
	{
		StarPickUpCue = StarPickUpSoundObject.Object;
		StarPickUpAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StarPickUpAudioComponent"));
	}

}

void AStarChaserGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage); //Must call to Super whenever you do a virtual function

	//handle options and parse out the ones you want
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);

	CollectiblesArraySetup(); //Setup BrightStar and Fairy Array
	Load();
	SetScoresAndNames(); //Add In Scores and Names from other Saved games
}

void AStarChaserGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnInitialFloor();
	SetMessages();
	SetAudio();
	SortHighScores();
}

int32 AStarChaserGameMode::BrightStarsCounter()
{
	int32 BrightStarCount = 0;
	for (int i = 0; i < BrightStarsActive.Num(); i++)
	{
		if (BrightStarsActive[i] == true)
		{
			BrightStarCount += 1;
		}
	}
	return BrightStarCount;
}

void AStarChaserGameMode::CollectiblesArraySetup()
{
	BrightStarsActive.SetNum(7);
	FairiesActive.SetNum(5);
	for (int i = 0; i < BrightStarsActive.Num(); i++)
	{
		BrightStarsActive[i] = false;
	}
	for (int i = 0; i < FairiesActive.Num(); i++)
	{
		FairiesActive[i] = false;
	}
}

void AStarChaserGameMode::DisplayGameOverMenu()
{
	UGameOverMenu* Widget = Cast<UGameOverMenu>(GameOverMenu->GetUserWidgetObject());
	Widget->AddToViewport();
}

void AStarChaserGameMode::DisplayHighScores()
{
	HighScores = NewObject<UWidgetComponent>(this);
	HighScores->RegisterComponent();
	HighScores->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	HighScores->SetWidgetClass(HighScoresClass);

	Backdrop = NewObject<UWidgetComponent>(this);
	Backdrop->RegisterComponent();
	Backdrop->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	Backdrop->SetWidgetClass(BackDropClass);

	if (HighScores && Backdrop)
	{
		UBackdrop* BackDropWidget = Cast<UBackdrop>(Backdrop->GetUserWidgetObject());
		UHighScores* HighScoresWidget = Cast<UHighScores>(HighScores->GetUserWidgetObject());
		//BackDropWidget->AddToViewport();
		HighScoresWidget->AddToViewport();
	}
}

void AStarChaserGameMode::DisplayFairyMessage()
{
	FairyMessage = NewObject<UWidgetComponent>(this);
	FairyMessage->RegisterComponent();
	FairyMessage->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	FairyMessage->SetWidgetClass(FairyMessageClass);

	if (FairyMessage)
	{
		UFairyMessage* FairyMessageWidget = Cast<UFairyMessage>(FairyMessage->GetUserWidgetObject());
		FairyMessageWidget->AddToViewport();
	}

}

int32 AStarChaserGameMode::FairiesCounter()
{
	int32 FariesCount = 0;
	for (int i = 0; i < FairiesActive.Num(); i++)
	{
		if (FairiesActive[i] == true)
		{
			FariesCount += 1;
		}
	}
	return FariesCount;
}

void AStarChaserGameMode::Load()
{
	UStarChaserSaveGame* SavedGame = UStarChaserSaveGame::Load(SlotName);
	if (SavedGame) SavedGame->DeserializeFromWorld(GetWorld());
	else UE_LOG(LogTemp, Warning, TEXT("Game Slot Not Found: %s"), *SlotName);
}

void AStarChaserGameMode::SaveAndQuit()
{
	Save();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void AStarChaserGameMode::Save()
{
	UStarChaserSaveGame* SavedGame = UStarChaserSaveGame::Load(SlotName);
	if (SavedGame)
	{
		SavedGame->SerializeFromWorld(GetWorld());
		SavedGame->Save();
	}
}

void AStarChaserGameMode::SetAudio()
{
	if (BootsOnAudioComponent && BootsOffAudioComponent)
	{
		BootsOnAudioComponent->SetSound(BootsOnCue);
		BootsOffAudioComponent->SetSound(BootsOffCue);
	}

	if (MagnetOnAudioComponent && MagnetOffAudioComponent)
	{
		MagnetOnAudioComponent->SetSound(MagnetOnCue);
		MagnetOffAudioComponent->SetSound(MagnetOffCue);
		
	}

	if (StarPickUpAudioComponent)
	{
		StarPickUpAudioComponent->SetSound(StarPickUpCue);
	}
	
}

void AStarChaserGameMode::SetHighScoreArray(TArray<int32> PlayerScoresArray)
{
	PlayerScores.Empty();
	for (int i = 0; i < PlayerScoresArray.Num(); i++)
	{

		PlayerScores.Add(PlayerScoresArray[i]);
	}
}

void AStarChaserGameMode::SetPlayerNameArray(TArray<FString> PlayerNamesArray)
{
	PlayerNames.Empty();
	for (int i = 0; i < PlayerNamesArray.Num(); i++)
	{

		PlayerNames.Add(PlayerNamesArray[i]);
	}
}

void AStarChaserGameMode::SetBrightStars(TArray<bool> BrightStarsArray)
{
	for (int i = 0; i < BrightStarsActive.Num(); i++)
	{
		BrightStarsActive[i] = false;
	}
	for (int i = 0; i < BrightStarsArray.Num(); i++)
	{

		BrightStarsActive[i] = BrightStarsArray[i];
	}
}

void AStarChaserGameMode::SetFairies(TArray<bool> FairiesArray)
{
	for (int i = 0; i < FairiesActive.Num(); i++)
	{
		FairiesActive[i] = false;
	}
	for (int i = 0; i < FairiesArray.Num(); i++)
	{

		FairiesActive[i] = FairiesArray[i];
	}
}

void AStarChaserGameMode::SetMessages()
{
	Messages.Add(Message1);
	Messages.Add(Message2);
	Messages.Add(Message3);
	Messages.Add(Message4);
	Messages.Add(Message5);
	Messages.Add(Message6);
	Messages.Add(Message7);
	Messages.Add(Message8);
}

void AStarChaserGameMode::SetScoresAndNames()
{
	TArray<FString> SlotNames = USaveGameIndex::LoadIndex()->GetSlotNames();

	for (int32 i = 0; i < SlotNames.Num(); i++)
	{
		UStarChaserSaveGame* IndexedGame = UStarChaserSaveGame::Load(SlotNames[i]);
		for (int j = 0; j < IndexedGame->PlayerScores.Num(); j++)
		{
			AllPlayerScores.Add(IndexedGame->PlayerScores[j]);
			AllPlayerNames.Add(IndexedGame->PlayerNames[j]);
		}
	}

}

void AStarChaserGameMode::SortHighScores()
{
	//Sort Global
	for (int i = 0; i < AllPlayerScores.Num(); i++)
	{
		for (int j = i + 1; j < AllPlayerScores.Num(); j++)
		{
			if (AllPlayerScores[j] > AllPlayerScores[i])
			{
				//Swap
				int32 tempint = AllPlayerScores[i];
				FString tempstring = AllPlayerNames[i];
				AllPlayerScores[i] = AllPlayerScores[j];
				AllPlayerNames[i] = AllPlayerNames[j];
				AllPlayerScores[j] = tempint;
				AllPlayerNames[j] = tempstring;
			}
		}
	}

	//Sort Local
	for (int i = 0; i < PlayerScores.Num(); i++)
	{
		for (int j = i + 1; j < PlayerScores.Num(); j++)
		{
			if (PlayerScores[j] > PlayerScores[i])
			{
				//Swap
				int32 tempint = PlayerScores[i];
				FString tempstring = PlayerNames[i];
				PlayerScores[i] = PlayerScores[j];
				PlayerNames[i] = PlayerNames[j];
				PlayerScores[j] = tempint;
				PlayerNames[j] = tempstring;
			}
		}
	}
}

void AStarChaserGameMode::SpawnInitialFloor()
{
	AMasterTile* InitialFloor;
	FVector InitialSpawnLocation = FVector(-4890, 0, 0);

	for (int32 i = 0; i < InitialFloorTileCount; ++i)
	{
		if (InitialFloorClass)
		{
			InitialFloor = GetWorld()->SpawnActor<AMasterTile>(InitialFloorClass, InitialSpawnLocation, FRotator(0,0,0));
			InitialSpawnLocation += FVector(ForwardSpawnOffset, 0, 0);
		}
	}

	bCanSpawnPlatform = true;
}

