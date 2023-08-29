// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileShoot.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileShoot::AProjectileShoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(150.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("ProjectileShoot"));

}

// Called when the game starts or when spawned
void AProjectileShoot::BeginPlay()
{
	Super::BeginPlay();
	
	


}

// Called every frame
void AProjectileShoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//생각해보니 나 왜 틱에서 하고 있엇지
	/*m_StartPos = this->GetActorLocation();
	m_DestPos = this->GetActorLocation() + FVector(1000, 0, 0);
	
	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, m_OutVelocity, m_StartPos, m_DestPos, GetWorld()->GetGravityZ(), m_arcValue))
	{
		m_ProjectilePathParams = FPredictProjectilePathParams(20.0f, m_StartPos, m_OutVelocity, 15.0f);
		
		m_ProjectilePathParams.OverrideGravityZ = GetWorld()->GetGravityZ();

		UGameplayStatics::PredictProjectilePath(this, m_ProjectilePathParams, m_ProjectilePathResult);


		SphereComponent->AddImpulse(m_OutVelocity);
	}*/

}

