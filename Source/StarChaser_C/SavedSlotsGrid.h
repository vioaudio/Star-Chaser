// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "DeleteSlot.h"
#include "SaveSlot.h"
#include "SavedSlotsGrid.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API USavedSlotsGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;

	UFUNCTION()
		void CreateSaveGame();

	UFUNCTION()
	void AddSavedSlot(int32 SavedSlotIndex, FString SavedSlotName);

	UFUNCTION()
		void ClearSlots();

	UFUNCTION()
	void DeleteSlot();
	
	UFUNCTION()
	void RefreshSlots();

	UFUNCTION()
		void RemoveSlots();

	int32 GetNumberOfSlots() const;

	FString SlotName;
	int32 Index = 0;
	bool DeleteMode = false;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UUniformGridPanel* SavedSlotsGrid;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* AddSlot;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* AddPlayerText;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* RemoveSlotsButton;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<USaveSlot> SaveSlotClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UDeleteSlot> DeleteSlotClass;
	
};
