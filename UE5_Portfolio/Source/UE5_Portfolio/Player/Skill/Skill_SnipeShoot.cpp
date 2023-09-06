// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_SnipeShoot.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/PlayerCharacter.h"
#include "../AnimInstance/MyAnimInstance.h"

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

	OnDestroyed.AddDynamic(this, &ASkill_SnipeShoot::OnActorDestroyed);
	SphereComponent->OnComponentHit.AddDynamic(this, &ASkill_SnipeShoot::OnHit);
}

// Called every frame
void ASkill_SnipeShoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//A += GetWorld()->GetDeltaSeconds();
	LifeTime += DeltaTime;
	if (LifeTime > 1.0f)
	{
		this->Destroy();
	}
}

void ASkill_SnipeShoot::OnActorDestroyed(AActor* _Actor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) PlayerCharacter == nullptr"), __FUNCTION__, __LINE__);
		return;
	}


	UMyAnimInstance* AnimInst = Cast<UMyAnimInstance>(Player->GetMesh()->GetAnimInstance());

	if (AnimInst == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) UMyAnimInstance == nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	
}

void ASkill_SnipeShoot::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ASkill_SnipeShoot::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionProfileName() == TEXT("Land"))
	{
		
	}
}

