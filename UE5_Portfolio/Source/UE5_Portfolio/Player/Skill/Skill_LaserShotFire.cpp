// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_LaserShotFire.h"
#include "../Character/PlayerCharacter.h"
#include "../AnimInstance/MyAnimInstance.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
ASkill_LaserShotFire::ASkill_LaserShotFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_LaserShotFire::BeginPlay()
{
	Super::BeginPlay();
	
	m_Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	OnDestroyed.AddDynamic(this, &ASkill_LaserShotFire::OnActorDestroy);
}

// Called every frame
void ASkill_LaserShotFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->StopMovement();
}

void ASkill_LaserShotFire::OnActorDestroy(AActor* _Destroy)
{
	UMyAnimInstance* PlayerAnimInst = Cast<UMyAnimInstance>(m_Player->GetMesh()->GetAnimInstance());
	PlayerAnimInst->SetMontagePaused(false);
	UAnimMontage* CurrentMontage = PlayerAnimInst->GetCurrentMontage();
	PlayerAnimInst->Montage_Resume(CurrentMontage);

	m_Player->m_AnimState = MyPlayerAnimState::IDLE;
}

