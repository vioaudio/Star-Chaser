// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class STARCHASER_C_API AExplosion : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundCue* ExplosionSound;

public:
	AExplosion();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Explode(AActor* OverlappedActor, AActor* OtherActor4);
	UPROPERTY()
		bool bSoundPlayed = false;
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* ExplosionAudioComponent;

};
