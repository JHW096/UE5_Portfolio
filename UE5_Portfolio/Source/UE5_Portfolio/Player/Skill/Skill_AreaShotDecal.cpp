// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaShotDecal.h"
#include "../PlayerController/MyPlayerController.h"
#include "Kismet/GamePlayStatics.h"

ASkill_AreaShotDecal::ASkill_AreaShotDecal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASkill_AreaShotDecal::BeginPlay()
{
	Super::BeginPlay();


	//Setting
	m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (m_PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u) Casting Fail MyPlayerController."), __FUNCTION__, __LINE__);
		return;
	}

	//Delegate
	OnDestroyed.AddDynamic(this, &ASkill_AreaShotDecal::OnActorDestroy);
}

void ASkill_AreaShotDecal::Tick(float _DeltaSecond)
{
	Super::Tick(_DeltaSecond);

	m_HitResult = m_PlayerController->GetHitResult();
	
	if (m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{

		FVector HitResultLocation = m_HitResult.Location;
		this->SetActorLocation(HitResultLocation);
	}

	
}

void ASkill_AreaShotDecal::OnActorDestroy(AActor* _Destroy)
{
	m_PlayerController->AreaShotDecalDestroyed();

}
