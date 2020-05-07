// Fill out your copyright notice in the Description page of Project Settings.


#include "MagnetPickUp.h"
#include "Components/AudioComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"
#include "StarPickUp.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"


AMagnetPickUp::AMagnetPickUp()
{
}

// Called when the game starts or when spawned
void AMagnetPickUp::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMagnetPickUp::MagnetOverlap);
}

bool AMagnetPickUp::CanCollide() const
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

void AMagnetPickUp::MagnetOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (CanCollide())
	{
		SetActorHiddenInGame(true);
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Runner) Runner->bMagnetActive = true;

		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->PlayMagnetOn();

		//Resets Timer On All Other Magnets
		for (TActorIterator<AMagnetPickUp> StrokeIterator(GetWorld()); StrokeIterator; ++StrokeIterator)
		{
			if (StrokeIterator->GetWorldTimerManager().IsTimerActive(DelayManager))
			{
				bPlayMagnetSound = false;
				StrokeIterator->GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &AMagnetPickUp::MagnetCoolDown, GameMode->MagnetCooldown, false);
			}
		}

		//Turns on Sphere Collider On All Stars
		for (TActorIterator<AStarPickUp> StrokeIterator(GetWorld()); StrokeIterator; ++StrokeIterator)
		{
			StrokeIterator->SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}

		GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &AMagnetPickUp::MagnetCoolDown, GameMode->MagnetCooldown, false);
	}
}

void AMagnetPickUp::MagnetCoolDown()
{
	UE_LOG(LogTemp, Warning, TEXT("Magnet Reset"));
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Runner) Runner->bMagnetActive = false;
	for (TActorIterator<AStarPickUp> StrokeIterator(GetWorld()); StrokeIterator; ++StrokeIterator)
	{
		if (StrokeIterator->SphereCollider)
		{ 
			StrokeIterator->SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	
	if (!Runner->bHasDied && bPlayMagnetSound)
	{
		GameMode->PlayMagnetOff();
	}
	
	Destroy();
}
