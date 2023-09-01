// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaShotStart.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "../PlayerController/MyPlayerController.h"






// Sets default values
ASkill_AreaShotStart::ASkill_AreaShotStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ASkill_AreaShotStart::BeginPlay()
{
	Super::BeginPlay();

	/*m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	FVector StartPos = this->GetActorLocation();
	FVector EndPos = m_PlayerController->GetHitResult().Location;
	m_EndLocation = (StartPos - EndPos).GetSafeNormal() * 500.0f;*/
	
	//Setting

}

// Called every frame
void ASkill_AreaShotStart::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
}

