// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StarChaserSaveGame.h"
#include "SaveGameIndex.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API USaveGameIndex : public USaveGame
{
	GENERATED_BODY()
	
public:
	static USaveGameIndex* LoadIndex();
	bool SaveIndex();

	void AddSaveGame(UStarChaserSaveGame* SaveGame);
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetSlotNames() const { return SlotNames; }
	void ClearSlotNames();
	void ClearSlotName(FString SlotName);

	UFUNCTION(BlueprintCallable)
		int32 GetSlotNameCount() { return SlotNames.Num(); }

private:
	static const FString SLOT_NAME;

	UPROPERTY()
		TArray<FString> SlotNames;
};
