// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fairy.generated.h"

UCLASS()
class STARCHASER_C_API AFairy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFairy();

	UFUNCTION()
	void WriteMessage(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	bool CanCollide();

	UPROPERTY()
		TArray<FString> MessagesTemp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
