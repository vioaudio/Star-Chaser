// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();

	UFUNCTION()
		void DisplaySavedSlotsGrid();
	UFUNCTION()
		void RemoveSavedSlotsGrid();
	UFUNCTION()
		void DisplayNameEntry();
	UFUNCTION()
		void SetSlotName(FString Name){SlotName = Name;}
	UFUNCTION(BlueprintCallable)
		FString GetSlotName() { return SlotName; }
	UFUNCTION(BlueprintCallable)
		void FadeOutMenuMusic();

	UPROPERTY()
	FString SlotName;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* SavedSlotsGrid;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* NameEntry;
};
