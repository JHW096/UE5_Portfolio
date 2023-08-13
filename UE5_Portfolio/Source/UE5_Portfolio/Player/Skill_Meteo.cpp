// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Meteo.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"


// Sets default values
ASkill_Meteo::ASkill_Meteo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(300.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("MeteoEnd"));

}

// Called when the game starts or when spawned
void ASkill_Meteo::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ASkill_Meteo::OnOverlapEnd);
	//SphereComponent->OnComponentHit.AddDynamic(this, &ASkill_Meteo::OnHit);

}

// Called every frame
void ASkill_Meteo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkill_Meteo::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if(OverlappedComp->GetCollisionProfileName() == TEXT("Monster"))	
	{
		
	}
	
}


