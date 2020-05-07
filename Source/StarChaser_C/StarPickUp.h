// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"	
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "StarPickUp.generated.h"

UCLASS()
class STARCHASER_C_API AStarPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarPickUp();

	virtual void Tick(float DeltaTime) override;

	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollider;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StarMesh;

	bool bIsActive = true;

	class UTimelineComponent* StarTimeline;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* SlideVsTime;

	UFUNCTION()
		void TimelineFloatReturn(float SlideValue);
	UFUNCTION()
		void OnTimelineFinished();

	FVector StartPos;
	FVector EndPos;

	//Delegate Function to be binded with TimelineVectorReturn
	FOnTimelineFloat InterpFunction{};
	//Delegate Function to be binded with OnTimelineFinished
	FOnTimelineEvent TimelineFinished{};

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void StarCollision(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void PlayTimeline();
	UFUNCTION()
		void AddStars();

private:
	UFUNCTION()
		bool CanCollide();


};
