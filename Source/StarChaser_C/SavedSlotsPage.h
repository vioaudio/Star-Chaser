// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "SavedSlotsGrid.h"
#include "SavedSlotsPage.generated.h"

UCLASS()
class STARCHASER_C_API ASavedSlotsPage : public AActor
{
	GENERATED_BODY()
	
public:	
	ASavedSlotsPage();

	void AddSaveSlot();

protected:
	virtual void BeginPlay() override;

private:
	void RefreshSlots();
};
