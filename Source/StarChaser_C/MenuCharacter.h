// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "StarChaserSaveGame.h"
#include "SavedSlotsGrid.h"
#include "MenuCharacter.generated.h"

UCLASS()
class STARCHASER_C_API AMenuCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMenuCharacter();
	UStarChaserSaveGame* SavedGame;
	FString SlotName;

protected:
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Save();
	void StartGame();
	void RefreshSlots();
	USavedSlotsGrid* GetSavedSlotsGrid() const;

	// Components 
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* SavedSlotsGrid;

};
