// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSword.h"
#include "Components/BoxComponent.h"
#include "GreatSwordCharacter.h"

// Sets default values
AGreatSword::AGreatSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGreatSword::BeginPlay()
{
	Super::BeginPlay();
	
	//m_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	//m_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	
}

void AGreatSword::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void AGreatSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreatSword::OnCharacterOverlap(UPrimitiveComponent* Overlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

