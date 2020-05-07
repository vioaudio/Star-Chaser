// Fill out your copyright notice in the Description page of Project Settings.


#include "StarPickUp.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"
#include "StarChaserGameMode.h"

// Sets default values
AStarPickUp::AStarPickUp()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
	StarMesh->SetupAttachment(RootComponent);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);

	//Timeline
	StarTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimeline"));
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

void AStarPickUp::AddStars()
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->CurrentStars += 1;
	GameMode->CurrentPoints += 25;
	GameMode->TotalStars += 1;
}

void AStarPickUp::BeginPlay()
{
	Super::BeginPlay();

	//Actor is created without sphere collider is Magnet is not active
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Runner->bMagnetActive == true) SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	if (Runner->bMagnetActive == false) SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OnActorBeginOverlap.AddDynamic(this, &AStarPickUp::StarCollision);
}

bool AStarPickUp::CanCollide() 
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Runner")))
		{
			if (bIsActive)
			{
				bIsActive = false;
				return true;
			}
			
		}
	}
	return false;
}

void AStarPickUp::PlayTimeline()
{
	if (SlideVsTime && StarTimeline)
	{
		//Adds in the vector curve to the timeline and connects it to the TimelineVectorReturns's Delegate
		StarTimeline->AddInterpFloat(SlideVsTime, InterpFunction, FName("Alpha"));
		StarTimeline->SetTimelineFinishedFunc(TimelineFinished);

		//Set Up Vectors
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		StartPos = GetActorLocation();
		EndPos = Runner->GetActorLocation();

		//Set Up Timeline Settings
		StarTimeline->SetLooping(false);
		StarTimeline->SetIgnoreTimeDilation(true); //for slow mo if needed
	

		//Start
		StarTimeline->PlayFromStart(); //Runs the Function until Timeline has ended
	}
}

void AStarPickUp::StarCollision(AActor* OverlappedActor, AActor* OtherActor)
{
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	if (CanCollide())
	{
		AddStars();
		ARunnerCharacter* Runner = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		UAudioComponent* StarSound = FindComponentByClass<UAudioComponent>();
		
		if (Runner->bMagnetActive == false)
		{
			SetActorHiddenInGame(true);
			GameMode->PlayStarPickUp();
			
		}
		if (Runner->bMagnetActive) PlayTimeline();
		
	}
}

void AStarPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStarPickUp::TimelineFloatReturn(float SlideValue)
{
	SetActorLocation(FMath::Lerp(StartPos, EndPos, SlideValue));
}

void AStarPickUp::OnTimelineFinished()
{
	UAudioComponent* StarSound = FindComponentByClass<UAudioComponent>();
	AStarChaserGameMode* GameMode = Cast<AStarChaserGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->PlayStarPickUp();
	Destroy();
}


