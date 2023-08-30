// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaShotStart.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
ASkill_AreaShotStart::ASkill_AreaShotStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(150.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("ProjectileShoot"));*/

	m_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	m_CapsuleComponent->SetCapsuleSize(0.5f, 0.5f);
	m_CapsuleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASkill_AreaShotStart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASkill_AreaShotStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

