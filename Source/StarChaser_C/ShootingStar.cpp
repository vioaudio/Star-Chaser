// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingStar.h"
#include "Components/AudioComponent.h"

// Sets default values
AShootingStar::AShootingStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootingStar::BeginPlay()
{
	Super::BeginPlay();
	UAudioComponent* ShootingStarSound = FindComponentByClass<UAudioComponent>();
	ShootingStarSound->SetVolumeMultiplier(1.1);
	ShootingStarSound->Play();
}

// Called every frame
void AShootingStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

