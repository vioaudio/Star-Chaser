// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstTile.generated.h"

UCLASS()
class STARCHASER_C_API AFirstTile : public AActor
{
	GENERATED_BODY()
	
//components
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* CollisionMesh;
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

public:	
	// Sets default values for this actor's properties
	AFirstTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
