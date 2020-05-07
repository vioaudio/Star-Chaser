// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FairyMessage.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UFairyMessage : public UUserWidget
{
	GENERATED_BODY()


	bool Initialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* FairyMessage;
	
};
