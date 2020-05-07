// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"
#include "Sound/SoundCue.h"
#include "StarChaserGameMode.h"
#include "UObject/ConstructorHelpers.h"


AExplosion::AExplosion()
{
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	static ConstructorHelpers::FObjectFinder<USoundCue> ExplosionSoundObject(TEXT("SoundCue'/Game/Audio/Cues/Explosion.Explosion'"));
	if (ExplosionSoundObject.Succeeded())
	{
		ExplosionSound = ExplosionSoundObject.Object;

		ExplosionAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionAudioComponent"));
		ExplosionAudioComponent->SetupAttachment(Root);

	}
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AExplosion::Explode);

	if (ExplosionAudioComponent && ExplosionSound)
	{
		ExplosionAudioComponent->SetSound(ExplosionSound);
	}

	if (!bSoundPlayed)
	{
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
		ExplosionAudioComponent->SetPitchMultiplier(FMath::RandRange(0.7f, 1.3f));
		ExplosionAudioComponent->Play();
		bSoundPlayed = true;
	}

	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Runner->bHasDied)
	{
		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->CurrentPoints += 25;

	}
}


void AExplosion::Explode(AActor* OverlappedActor, AActor* OtherActor4)
{
}