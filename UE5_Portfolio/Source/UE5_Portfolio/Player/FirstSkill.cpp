// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSkill.h"
#include "Components/SphereComponent.h"

// Sets default values
AFirstSkill::AFirstSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(300.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("FirstSkill"));

}

// Called when the game starts or when spawned
void AFirstSkill::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AFirstSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
