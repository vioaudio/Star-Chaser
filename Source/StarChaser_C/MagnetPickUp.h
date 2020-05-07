// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagnetPickUp.generated.h"

UCLASS()
class STARCHASER_C_API AMagnetPickUp : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMagnetPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void MagnetOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void MagnetCoolDown();

private:
	UFUNCTION()
		bool CanCollide() const;

	FTimerHandle DelayManager;
	bool bPlayMagnetSound = true;;


};
