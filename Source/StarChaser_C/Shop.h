// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Shop.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UShop : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* MagnetPrice;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* BootsPrice;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* SkinPriceText;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* BuyMagnet;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* BuyBoots;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* Skin;

private:
	UFUNCTION()
	void UpgradeMagnet();
	UFUNCTION()
	void UpgradeBoots();
	UFUNCTION()
	void UpgradeSkin();
};
