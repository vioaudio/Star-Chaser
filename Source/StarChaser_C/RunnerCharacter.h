// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "GameOverMenu.h"
#include "MasterTile.h"
#include "StarChaserGameMode.h"
#include "StarChaserSaveGame.h"
#include "ShootingStar.h"
#include "RunnerCharacter.generated.h"


UCLASS()
class STARCHASER_C_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	//Components

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	class UTimelineComponent* MovementTimeline;

public:
	// Sets default values for this character's properties
	ARunnerCharacter();

	//Movement
	UPROPERTY()
		int32 Lane = 1;
	UPROPERTY()
		int32 NewLane;
	UPROPERTY()
		TArray<float> YPosition;
	UPROPERTY(EditAnywhere)
		class UCurveFloat* YvsTime;
	UPROPERTY()
		float StartY;
	UPROPERTY()
		float EndY;
	UPROPERTY(EditAnywhere)
		float YOffset = 100.f;
	UPROPERTY()
		float StartingSpeed;
	UPROPERTY(EditAnywhere)
		float SpeedUpRate = 1.1f;

	//Power
	bool bMagnetActive = false;
	bool bBootsActive = false;

	//TimelineFunctions
	UFUNCTION()
		void TimelineFloatReturn(float value);
	UFUNCTION()
		void OnTimelineFinished();

	//Delegate Function to be binded with TimelineFloatReturn
	FOnTimelineFloat InterpFunction{};

	//Delegate Function to be binded with OnTimelineFinished
	FOnTimelineEvent TimelineFinished{};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	UFUNCTION(BlueprintCallable)
	void Death();

	//Getters
	float GetSpeedUpRate(){return SpeedUpRate;}

	//SavedGame
	FString SlotName;
	
	//State
	bool bHasDied = false;
	bool bIntCounter = false;

private:
	void ForceLanding();
	void MoveForward(float Value);
	void RunTimeline(float Index);
	void SetShiftAmount();
	void ShiftLeft();
	void ShiftRight();
	void ShootingStar();

	

	//Score
	void SetScore();
	void CreateHighScoreList();

	//Configuration
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AShootingStar> ShootingStarClass;
	UPROPERTY(EditAnywhere)
		FVector ShootingStarSpawnOffset = FVector(0, 0, 0);

	

};
