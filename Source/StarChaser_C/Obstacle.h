// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrightStar.h"
#include "Explosion.h"
#include "Fairy.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class STARCHASER_C_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(EditAnywhere)
		FVector SpawnOffset = FVector(0, 0, 0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void CallDeath (AActor* OverlappedActor, AActor* OtherActor4);

	UFUNCTION()
		void DestroyStar();

	void SpawnPickUp();

	//Configuration
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFairy> LightFairy;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFairy> SkyFairy;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFairy> WaterFairy;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFairy> DarkFairy;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFairy> LoveFairy;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABrightStar> BrightStar;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AExplosion> ExplosionClass;

	//State
	bool IsRunner() const;
	bool IsStar() const;
	bool bIsOverlapped = false;
};
