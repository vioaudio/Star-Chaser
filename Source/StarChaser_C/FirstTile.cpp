// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstTile.h"
#include "Components/BoxComponent.h"

// Sets default values
AFirstTile::AFirstTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AFirstTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

