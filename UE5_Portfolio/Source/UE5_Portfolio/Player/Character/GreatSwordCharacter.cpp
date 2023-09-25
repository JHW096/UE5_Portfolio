// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordCharacter.h"
#include "NiagaraComponent.h"

AGreatSwordCharacter::AGreatSwordCharacter()
{
	//SKELETALMESH_SET
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> PLAYER_SKEL_MESH(
			TEXT("/Script/Engine.SkeletalMesh'/Game/GreatSword/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'")
		);

		if (PLAYER_SKEL_MESH.Succeeded())
		{
			GetMesh()->SetSkeletalMesh(PLAYER_SKEL_MESH.Object);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s(%u) : Player_SkeletalMesh = Nullptr"), __FUNCTION__, __LINE__);
		}
	}

	{
		
	}

	m_AnimState = GreatSwordAnimState::IDLE;
}

void AGreatSwordCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGreatSwordCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAction();

	if (m_AnimState == GreatSwordAnimState::CKey || m_AnimState == GreatSwordAnimState::QKey)
	{
		isAttacking = true;
	}
	else
	{
		isAttacking = false;
	}
}

void AGreatSwordCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGreatSwordCharacter::MoveAction()
{
	if (m_AnimState == GreatSwordAnimState::CKey)
	{
		return;
	}

	if (m_AnimState == GreatSwordAnimState::WKey)
	{
		return;
	}

	if (m_AnimState == GreatSwordAnimState::EKey)
	{
		return;
	}

	if (m_AnimState == GreatSwordAnimState::RKey)
	{
		return;
	}

	if (m_AnimState == GreatSwordAnimState::DASH)
	{
		return;
	}

	if (m_AnimState == GreatSwordAnimState::QKey)
	{
		return;
	}

	m_AnimState = GetVelocity().Size() > 1.0f ? GreatSwordAnimState::JOG_FWD : GreatSwordAnimState::IDLE;
}


