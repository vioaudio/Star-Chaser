// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Types/SlateEnums.h"
#include "NameEntry.generated.h"

/**
 * 
 */
UCLASS()
class STARCHASER_C_API UNameEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:

	bool Initialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UEditableText* NameEntry;
};
