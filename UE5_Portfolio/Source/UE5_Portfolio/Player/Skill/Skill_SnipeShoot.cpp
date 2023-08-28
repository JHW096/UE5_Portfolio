// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_SnipeShoot.h"
#include "Components/SphereComponent.h"

// Sets default values
ASkill_SnipeShoot::ASkill_SnipeShoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("SnipeShoot"));
}

// Called when the game starts or when spawned
void ASkill_SnipeShoot::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ASkill_SnipeShoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//A += GetWorld()->GetDeltaSeconds();
	LifeTime += DeltaTime;
	if (LifeTime > 1.5f)
	{
		this->Destroy();
	}
}

