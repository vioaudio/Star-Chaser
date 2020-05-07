// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameOverMenu.h"
#include "Kismet/GameplayStatics.h"
#include "MasterTile.h"
#include "StarChaserGameMode.h"
#include "StarChaserSaveGame.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(42.f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input	
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//Timeline Setup
	MovementTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimeline"));
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn")); 
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetShiftAmount();

	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode->bRunnerRunning) GetCharacterMovement()->DisableMovement();
}

void ARunnerCharacter::OnTimelineFinished()
{
}

void ARunnerCharacter::CreateHighScoreList()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	UE_LOG(LogTemp, Warning, TEXT("Size of Player Scores After Death: %d"), GameMode->AllPlayerScores.Num())
	//Sort Global
	for (int i = 0; i < GameMode->AllPlayerScores.Num(); i++)
	{
		for (int j = i + 1; j < GameMode->AllPlayerScores.Num(); j++)
		{
			if (GameMode->AllPlayerScores[j] > GameMode->AllPlayerScores[i])
			{
				//Swap
				int32 tempint = GameMode->AllPlayerScores[i];
				FString tempstring = GameMode->AllPlayerNames[i];
				GameMode->AllPlayerScores[i] = GameMode->AllPlayerScores[j];
				GameMode->AllPlayerNames[i] = GameMode->AllPlayerNames[j];
				GameMode->AllPlayerScores[j] = tempint;
				GameMode->AllPlayerNames[j] = tempstring;
			}
		}
	}

	//Sort Local
	for (int i = 0; i < GameMode->PlayerScores.Num(); i++)
	{
		for (int j = i + 1; j < GameMode->PlayerScores.Num(); j++)
		{
			if (GameMode->PlayerScores[j] > GameMode->PlayerScores[i])
			{
				//Swap
				int32 tempint = GameMode->PlayerScores[i];
				FString tempstring = GameMode->PlayerNames[i];
				GameMode->PlayerScores[i] = GameMode->PlayerScores[j];
				GameMode->PlayerNames[i] = GameMode->PlayerNames[j];
				GameMode->PlayerScores[j] = tempint;
				GameMode->PlayerNames[j] = tempstring;
			}
		}
	}
	
	//Print
	for (int32 i = 0; i < GameMode->AllPlayerScores.Num() && i < 11; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *GameMode->AllPlayerNames[i], GameMode->AllPlayerScores[i]);
	}
	GameMode->Save();
}

void ARunnerCharacter::Death()
{
	if (!bHasDied)
	{
		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		//RagDoll
		FindComponentByClass<USkeletalMeshComponent>()->SetSimulatePhysics(true);
		GetCharacterMovement()->DisableMovement();
		GameMode->bRunnerRunning = false;
		SetScore();
		CreateHighScoreList();

		//GameOver
		GameMode->DisplayGameOverMenu();
	
		bHasDied = true;
		
	}
}


void ARunnerCharacter::ForceLanding()
{
	GetCharacterMovement()->AddImpulse(FVector(0, 0, -3000.f), true);
}

void ARunnerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARunnerCharacter::RunTimeline(float Index)
{
	if (YvsTime && MovementTimeline)
	{
		//Adds in the float curve to the timeline and connects it to the InterpFunction's Delegate
		MovementTimeline->AddInterpFloat(YvsTime, InterpFunction, FName("Alpha"));
		MovementTimeline->SetTimelineFinishedFunc(TimelineFinished);

		//Set Up Y Positions
		StartY = GetActorLocation().Y;
		EndY = YPosition[Index];

		//Set Up Timeline Settings
		MovementTimeline->SetLooping(false);
		MovementTimeline->SetIgnoreTimeDilation(true); //for slow mo if needed

		//Start
		MovementTimeline->PlayFromStart(); //Runs the InterpFunction until Timeline has ended
	}
}

//Sets High Score & Resets Current Score to Zero
void ARunnerCharacter::SetScore() 
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->CurrentPoints > GameMode->HighestScore)
	{
		GameMode->SetHighestScore(GameMode->CurrentPoints);
	}
	UE_LOG(LogTemp, Warning, TEXT("High Score is %d"), GameMode->HighestScore);

	//Add Highscore to Highscore List Arrays

	GameMode->PlayerScores.Add(GameMode->CurrentPoints);
	GameMode->PlayerNames.Add(GameMode->CurrentName);
	GameMode->AllPlayerScores.Add(GameMode->CurrentPoints);
	GameMode->AllPlayerNames.Add(GameMode->CurrentName);
	GameMode->Save();
	UE_LOG(LogTemp, Warning, TEXT("Size of Local PlayerScores: %d"), GameMode->PlayerScores.Num());
	
}

//Sets up Y Position Coordinates for Character Movement 
void ARunnerCharacter::SetShiftAmount()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	YPosition.SetNum(3);
	YPosition[0] = GameMode->GetLaneOneOffset();
	YPosition[1] = GameMode->GetLaneTwoOffset();
	YPosition[2] = GameMode->GetLaneThreeOffset();
}


// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ARunnerCharacter::ShiftLeft);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ARunnerCharacter::ShiftRight);
	PlayerInputComponent->BindAction("ForceLanding", IE_Pressed, this, &ARunnerCharacter::ForceLanding);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ARunnerCharacter::ShootingStar);
}

void ARunnerCharacter::ShiftLeft()
{
	Lane += -1;
	if (Lane < 0)
	{
		Lane = 0;
		return;
	}
	RunTimeline(Lane);
	UE_LOG(LogTemp, Warning, TEXT("ShiftLeft"));
}

void ARunnerCharacter::ShiftRight()
{	
	Lane += 1;
	if (Lane > 2)
	{
		Lane = 2;
		return;
	}
	RunTimeline(Lane);
}

void ARunnerCharacter::ShootingStar()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->CurrentStars < 1) return; //Check

	//Spawn
	FVector SpawnLocation = GetActorLocation() + ShootingStarSpawnOffset;
	if (!ShootingStarClass) return;
	GetWorld()->SpawnActor<AShootingStar>(ShootingStarClass, SpawnLocation, GetActorRotation());

	//Set Star Count
	if (GameMode->bNovaSkin)
	{
		if (bIntCounter)
		{
			GameMode->CurrentStars += -1;
			bIntCounter = false;
			return;
		}

		if (!bIntCounter) bIntCounter = true;
	}
	else
	{
		GameMode->CurrentStars += -1;
	}
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(1.f);
}

void ARunnerCharacter::TimelineFloatReturn(float value)
{
	FVector StartLocation = FVector(GetActorLocation().X, StartY, GetActorLocation().Z);
	FVector EndLocation = FVector(GetActorLocation().X, EndY, GetActorLocation().Z);
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, value));
}
