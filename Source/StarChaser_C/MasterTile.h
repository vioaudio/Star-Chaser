// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BootsPickUp.h"
#include "CloudPlatform.h"
#include "GameFramework/Actor.h"
#include "MagnetPickUp.h"
#include "Obstacle.h"
#include "StarPickUp.h"
#include "MasterTile.generated.h"


UCLASS()
class STARCHASER_C_API AMasterTile : public AActor
{
	GENERATED_BODY()

//components
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* CollisionMesh;
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

public:	
	// Sets default values for this actor's properties
	AMasterTile();
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


private: 
	FVector FloorSpawnLocation;
	UPROPERTY()
	FVector LaneOneSpawnLocation;
	UPROPERTY()
	FVector LaneTwoSpawnLocation;
	UPROPERTY()
	FVector LaneThreeSpawnLocation;
	FTimerHandle DelayManager;
	FTimerHandle ObstacleDelayManager;
	FTimerHandle CloudPlatofrmDelayManager;

	//CallBack
	UFUNCTION()
		void DestroyFloor();
	UFUNCTION()
		void SpawnFloorTile(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void SpawnObstacles(int Lane, bool CloudPlatform);

	//Configuration
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMasterTile> FloorTileClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AObstacle> HurdleClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AObstacle> BoxClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AObstacle> FlyingBoxClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AObstacle> FlyingBoxClassTwo;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABootsPickUp> BootsPickUpClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AStarPickUp> StarPickUpClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMagnetPickUp> MagnetPickUpClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACloudPlatform> CloudPlatformClassOne;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACloudPlatform> CloudPlatformClassTwo;
	
	//State
	bool CanCollide() const;
	int BoxesInRow = 0;
	
	UFUNCTION()
		void CloudPlatformReset();
	UFUNCTION()
		void ObstacleReset();
};
