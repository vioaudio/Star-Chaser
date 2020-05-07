// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DeleteSlot.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UDeleteSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSaveSlotName(FString NewSaveSlotName, FString PlayerName);

	int32 Index;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* Name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* DeleteSaveSlotButton;
	
private:
	//State
	FString SaveSlotName;
	bool bClickable = true;

	UFUNCTION()
		void ButtonClicked();
};
