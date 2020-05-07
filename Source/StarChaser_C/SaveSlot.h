// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SaveSlot.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API USaveSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSaveSlotName(FString NewSaveSlotName, FString PlayerName);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* Name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* OpenSaveSlotButton;


private:
	UFUNCTION()
		void ButtonClicked();
	UFUNCTION()
		void OpenLevel();

	//State
	FString SaveSlotName;
	FTimerHandle DelayManager;
	
};
