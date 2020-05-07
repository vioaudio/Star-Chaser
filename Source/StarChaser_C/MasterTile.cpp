// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterTile.h"
#include "BootsPickUp.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"
#include "StarChaserGameMode.h"
#include "TimerManager.h"

// Sets default values
AMasterTile::AMasterTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <USceneComponent> (TEXT("Root"));
	SetRootComponent(Root);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	OnActorBeginOverlap.AddDynamic(this, &AMasterTile::SpawnFloorTile);
	
	//SetFloorSpawnPoint
	FloorSpawnLocation = (GetActorForwardVector() * GameMode->GetForwardSpawnOffset()) * GameMode->GetInitialFloorTileCount() +  GetActorLocation();

	//SetObstacleSpawnPoints
	LaneOneSpawnLocation = GetActorRightVector() * GameMode->GetLaneOneOffset() + GetActorLocation();
	LaneTwoSpawnLocation = GetActorRightVector() * GameMode->GetLaneTwoOffset() + GetActorLocation();
	LaneThreeSpawnLocation = GetActorRightVector() * GameMode->GetLaneThreeOffset() + GetActorLocation();

	SpawnObstacles(1, GameMode->bCanSpawnPlatform);
	SpawnObstacles(2, false);
	SpawnObstacles(3, false);
} 

bool AMasterTile::CanCollide() const //Only Runner Can Spawn New Floor Tile
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

void AMasterTile::CloudPlatformReset()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->bCanSpawnPlatform = true;
	UE_LOG(LogTemp, Warning, TEXT("CloudPlatform Cooldown Reset"));
}


void AMasterTile::DestroyFloor()
{
	GetWorldTimerManager().ClearTimer(DelayManager);
	Destroy();
}

void AMasterTile::ObstacleReset()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->bCanSpawnObstacle = true;
	UE_LOG(LogTemp, Warning, TEXT("Obstacle Cooldown Reset"));
}


void AMasterTile::SpawnFloorTile(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!FloorTileClass) return;
	

	if (CanCollide())
	{
		//Spawn
		GetWorld()->SpawnActor<AMasterTile>(FloorTileClass, FloorSpawnLocation, GetActorRotation());

		//DestroyFloor
		GetWorld()->GetTimerManager().SetTimer(DelayManager, this, &AMasterTile::DestroyFloor, 30.f, false);

		//IncreaseSpeed
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Runner->GetCharacterMovement()->MaxWalkSpeed < 2000)
		{
			Runner->GetCharacterMovement()->MaxWalkSpeed = Runner->GetCharacterMovement()->MaxWalkSpeed * Runner->GetSpeedUpRate();
		}

		//Add Points
		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		int32 Points = GameMode->CurrentPoints + 15;
		GameMode->SetCurrentPoints(Points);
		UE_LOG(LogTemp, Warning, TEXT("Current Points: %d"), Points);
	}
}

void AMasterTile::SpawnObstacles(int Lane, bool CloudPlatform)
{
	float Creator = FMath::FRandRange(0.f, 100.f); //Decides what obstace will spawn
	FVector SpawnLocation;
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Lane == 1) SpawnLocation = LaneOneSpawnLocation;
	else if (Lane == 2) SpawnLocation = LaneTwoSpawnLocation;
	else if (Lane == 3) SpawnLocation = LaneThreeSpawnLocation;
	
	//HURDLE
	if (Creator < 20 && GameMode->bCanSpawnObstacle)
	{
		GetWorld()->SpawnActor<AObstacle>(HurdleClass, SpawnLocation, GetActorRotation());
	}

	//BOX
	else if (Creator > 20 && Creator < 36.5f && GameMode->bCanSpawnObstacle)
	{
		if (BoxesInRow < 2) //Prevents Three Boxes In One Row
		{
			GetWorld()->SpawnActor<AObstacle>(BoxClass, SpawnLocation, GetActorRotation());
			++BoxesInRow;
		}
	}

	//BOOTS PICK UP
	else if (Creator > 36.5 && Creator < 37.5 && GameMode->bCanSpawnObstacle && !Runner->bBootsActive)
	{
		GetWorld()->SpawnActor<ABootsPickUp>(BootsPickUpClass, SpawnLocation, GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Boots Spawned"));
	}

	//MAGNET PICK UP
	else if (Creator > 37.5 && Creator < 39 && GameMode->bCanSpawnObstacle && !Runner->bMagnetActive)
	{
		GetWorld()->SpawnActor<AMagnetPickUp>(MagnetPickUpClass, SpawnLocation, GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Magnet Spawned"));

	}

	//STAR PICK UP
	else if (Creator > 39 && Creator < 73 && GameMode->bCanSpawnObstacle)
	{
		GetWorld()->SpawnActor<AStarPickUp>(StarPickUpClass, SpawnLocation, GetActorRotation());
	}

	//ClOUD PLATFORM 1
	else if (Creator > 73 && Creator < 80 && CloudPlatform)
	{
		GetWorld()->SpawnActor<ACloudPlatform>(CloudPlatformClassOne, LaneTwoSpawnLocation, GetActorRotation());
		GameMode->bCanSpawnPlatform = false;
		GameMode->bCanSpawnObstacle = false;
		GetWorld()->GetTimerManager().SetTimer(CloudPlatofrmDelayManager, this, &AMasterTile::CloudPlatformReset, 20.f, false);
		GetWorld()->GetTimerManager().SetTimer(ObstacleDelayManager, this, &AMasterTile::ObstacleReset, 5.f, false);
	}

	//CLOUD PLATFORM 2
	else if (Creator > 80 && Creator < 87 && CloudPlatform)
	{
		GetWorld()->SpawnActor<ACloudPlatform>(CloudPlatformClassTwo, LaneTwoSpawnLocation, GetActorRotation());
		GameMode->bCanSpawnPlatform = false;
		GameMode->bCanSpawnObstacle = false;
		GetWorld()->GetTimerManager().SetTimer(CloudPlatofrmDelayManager, this, &AMasterTile::CloudPlatformReset, 20.f, false);
		GetWorld()->GetTimerManager().SetTimer(ObstacleDelayManager, this, &AMasterTile::ObstacleReset, 5.f, false);
	}

	//FLYING BOX
	else if (Creator > 87 && Creator < 93.5 && GameMode->bCanSpawnObstacle)
	{
		GetWorld()->SpawnActor<AObstacle>(FlyingBoxClass, SpawnLocation + FVector(-1625, 731, 163), GetActorRotation());

	}

	//FLYING BOX 2
	else if (Creator > 93.5 && Creator < 100 && GameMode->bCanSpawnObstacle)
	{
		GetWorld()->SpawnActor<AObstacle>(FlyingBoxClassTwo, SpawnLocation + FVector(-1016, 248, 145), GetActorRotation());
	}
}

void AMasterTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


