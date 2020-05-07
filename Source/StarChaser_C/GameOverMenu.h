// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameOverMenu.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void ShowHighScores();
	UFUNCTION()
	void ShowMenu();
	UFUNCTION()
	void Shop();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* DreamOn;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* HighScores;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* Menu;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* StarShop;
};
