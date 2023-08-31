// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_AreaShotStart.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "../PlayerController/MyPlayerController.h"
#include "../Character/PlayerCharacter.h"





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

	//Setting
	m_PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_HitResult = m_PlayerController->GetHitResult();

	//Delegate 
	OnDestroyed.AddDynamic(this, &ASkill_AreaShotStart::OnActorDestroy);
}

// Called every frame
void ASkill_AreaShotStart::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);


	if (m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, m_HitResult))
	{
		FVector HitResultLocation = m_HitResult.Location;
		this->SetActorLocation(HitResultLocation);
	}
}

void ASkill_AreaShotStart::OnActorDestroy(AActor* _Destroy)
{
	if (m_AreaShotFire == nullptr)
	{
		return;
	}

	APlayerCharacter* Player = Cast<APlayerCharacter>(m_PlayerController->GetPawn());
	TArray<UActorComponent*> ComponentsByTag = Player->GetComponentsByTag(USceneComponent::StaticClass(), TEXT("BulletPos"));
	
	FVector AreaShotSpawnLocation = Cast<USceneComponent>(ComponentsByTag[0])->GetComponentLocation();
	
	FTransform AreaShotSpawnTransform;
	AreaShotSpawnTransform.SetLocation(AreaShotSpawnLocation);

	AActor* AreaShotFireActor = GetWorld()->SpawnActor<AActor>(m_AreaShotFire, AreaShotSpawnTransform);

	m_PlayerController->SetOnArea(false); 
}

