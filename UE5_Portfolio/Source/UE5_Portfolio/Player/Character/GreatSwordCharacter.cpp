// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSwordCharacter.h"

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

	m_AnimState = GreatSwordAnimState::IDLE;
}

void AGreatSwordCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGreatSwordCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGreatSwordCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


