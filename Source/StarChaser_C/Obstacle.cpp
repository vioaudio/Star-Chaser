// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AObstacle::CallDeath);
}

void AObstacle::CallDeath(AActor* OverlappedActor, AActor* OtherActor4)
{
	if (IsRunner())
	{
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Runner) Runner->Death();
	}

	if (!bIsOverlapped)
	{
		if (IsStar())
		{
			bIsOverlapped = true;
			UE_LOG(LogTemp, Warning, TEXT("IS A Star"));
			DestroyStar();
			SpawnPickUp();
			Destroy();
		}
	}
	
}

bool AObstacle::IsRunner() const //Only Runner Can Cause Death
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

bool AObstacle::IsStar() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Star")))
		{
			return true;
		}
	}
	return false;
}

void AObstacle::DestroyStar()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Star")))
		{
			OverlappingActor->Destroy();
		}
	}
}

void AObstacle::SpawnPickUp()
{
	UBoxComponent* BoxComponent = FindComponentByClass<UBoxComponent>();
	if (BoxComponent)
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Warning, TEXT("Box Collider Deactivated"));
	}

	float Creator = FMath::FRandRange(0.f, 100.f); //Decides what obstace will spawn
	FVector SpawnLocation = GetActorLocation() + SpawnOffset;
	FRotator SpawnRotation = GetActorRotation();

	
	//Exlosion
	UStaticMeshComponent* StaticMesh = FindComponentByClass<UStaticMeshComponent>();

	if (ExplosionClass && StaticMesh) (GetWorld()->SpawnActor<AExplosion>(ExplosionClass, GetActorLocation() + StaticMesh->GetRelativeLocation(), SpawnRotation));

	//Light
	if (Creator < 6 && LightFairy)
	{
		GetWorld()->SpawnActor<AFairy>(LightFairy, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Light Fairy Spawned"));
	}

	//Sky
	else if (Creator > 6 && Creator < 12 && SkyFairy)
	{
			GetWorld()->SpawnActor<AFairy>(SkyFairy, SpawnLocation, SpawnRotation);
			UE_LOG(LogTemp, Warning, TEXT("Sky Fairy Spawned"));
	}

	//Water
	else if (Creator > 12 && Creator < 18 && WaterFairy)
	{
		GetWorld()->SpawnActor<AFairy>(WaterFairy, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Water Fairy Spawned"));
	}

	//Dark
	else if (Creator > 18 && Creator < 24 && DarkFairy)
	{
		GetWorld()->SpawnActor<AFairy>(DarkFairy, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Dark Fairy Spawned"));
	}

	//Love
	else if (Creator > 24 && Creator < 30 && LoveFairy)
	{
		GetWorld()->SpawnActor<AFairy>(LoveFairy, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Love Fairy Spawned"));
	}

	//BrightStar
	else if (Creator > 30 && Creator < 33 && BrightStar)
	{
		GetWorld()->SpawnActor<ABrightStar>(BrightStar, SpawnLocation, GetActorRotation());
	}
}
