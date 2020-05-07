// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "GameOverMenu.h"
#include "SavedSlotsGrid.h"
#include "UIMaster.generated.h"

UCLASS()
class STARCHASER_C_API AUIMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	AUIMaster();

	//UI Calls
	UFUNCTION()
		void DisplayGameOverMenu() ;
	UFUNCTION()
		void DisplaySavedSlotsGrid() ;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* GameOverMenu;
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* SavedSlotsGrid;

};
