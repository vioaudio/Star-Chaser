// Fill out your copyright notice in the Description page of Project Settings.


#include "Fairy.h"
#include "StarChaserGameMode.h"


// Sets default values
AFairy::AFairy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFairy::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AFairy::WriteMessage);
}

bool AFairy::CanCollide()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Runner")))
		{
			return true;
		}
	}
	return false;
}

void AFairy::WriteMessage(AActor* OverlappedActor, AActor* OtherActor)
{
	if (CanCollide())
	{
		
		AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->CurrentPoints += 100;
		GameMode->CurrentStars += 25;
		
		if (GameMode->Messages.Num() == 0)
		{
			GameMode->SetMessages();
		}
		
		int32 LowerRange = 0;
		int32 HigherRange = GameMode->Messages.Num();
		int32 Index = FMath::RandRange(LowerRange, HigherRange - 1);
		FString OutputMessage = GameMode->Messages[Index];
		GameMode->Messages.RemoveAt(Index, 1, true);

		UE_LOG(LogTemp, Warning, TEXT("Message Temp is %d In Length"), GameMode->Messages.Num());
		GameMode->OutputMessage = OutputMessage;
		GameMode->DisplayFairyMessage();
	}

}


// Called every frame
void AFairy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

