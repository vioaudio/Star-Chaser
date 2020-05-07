// Fill out your copyright notice in the Description page of Project Settings.


#include "BootsPickUp.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"



// Sets default values
ABootsPickUp::ABootsPickUp()
{
}

// Called when the game starts or when spawned
void ABootsPickUp::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ABootsPickUp::PowerUp);
}

bool ABootsPickUp::CanCollide() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Runner")))
		{
			return true;
		}
	}
	return false;
}

void ABootsPickUp::DestroyBoots()
{
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Runner->GetCharacterMovement()->JumpZVelocity = 600.f;
	GetWorldTimerManager().ClearTimer(DelayManager);
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (!Runner->bHasDied)
	{
		GameMode->PlayBootsOff();
	}

	Runner->bBootsActive = false;
	UE_LOG(LogTemp, Warning, TEXT("boot cooldown"));
	Destroy();
}

void ABootsPickUp::PowerUp(AActor* OverlappedActor, AActor* OtherActor)
{
	if (CanCollide())				
	{
		SetActorHiddenInGame(true);
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Runner->GetCharacterMovement()->JumpZVelocity = 1200.f;
		Runner->bBootsActive = true;
		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->PlayBootsOn();

		//Resets Timer On All Other Boots
		for (TActorIterator<ABootsPickUp> StrokeIterator(GetWorld()); StrokeIterator; ++StrokeIterator)
		{
			if (StrokeIterator->GetWorldTimerManager().IsTimerActive(DelayManager))
			{
				StrokeIterator->GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &ABootsPickUp::DestroyBoots, GameMode->BootsCooldown, false);
			}
		}
		GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &ABootsPickUp::DestroyBoots, GameMode->BootsCooldown, false);
	}
}


