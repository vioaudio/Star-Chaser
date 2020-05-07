// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BootsPickUp.generated.h"

UCLASS()
class STARCHASER_C_API ABootsPickUp : public AActor
{
	GENERATED_BODY()
public:	
	ABootsPickUp();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void PowerUp(AActor* OverlappedActor, AActor* OtherActor); 
	UFUNCTION()
		bool CanCollide() const;
	UFUNCTION()
		void DestroyBoots();

	FTimerHandle DelayManager;


};
