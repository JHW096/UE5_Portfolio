// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	{
		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = true;
	}

	//PLAYER_ROTATE_SET
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}

	//PLAYER_MOVEMENT_SET
	{
		//Player_RotateRate_Set_
		GetCharacterMovement()->bOrientRotationToMovement = true;
		
		//Player_Rotation_Rate_for_Seconds_
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);

		//Player_Start_Plane
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
	}

	//SPRINGARMCOMPONENET
	{
		m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARMCOMPONENT"));
		m_SpringArmComponent->SetupAttachment(RootComponent);						//Attach CapsuleComp
		m_SpringArmComponent->SetUsingAbsoluteRotation(true);						//Don't want arm to rotate when character does
		m_SpringArmComponent->TargetArmLength = 1250.0f;							//Length_Between_Character_to_PlayerCamera
		m_SpringArmComponent->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f));	//for_TopDownView_Rotation
		m_SpringArmComponent->bDoCollisionTest = false;								// Don't want ot pull camera in when it collides with level
	}

	//CAMERACOMPONENT
	{
		m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TOPDOWNCAMERA"));
		m_CameraComponent->SetupAttachment(m_SpringArmComponent);
		m_CameraComponent->bUsePawnControlRotation = false; // Camera does not rotaterelative to arm
	}

	//SKELETALMESH_SET
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> PLAYER_SKEL_MESH(
			TEXT("/Script/Engine.SkeletalMesh'/Game/Player/Resource/Mesh/Player_SkelMesh.Player_SkelMesh'")
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


	m_AnimState = MyPlayerAnimState::IDLE;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAction();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MoveAction()
{
	if (m_AnimState == MyPlayerAnimState::DASH)
	{
		return;
	}
	m_AnimState = GetVelocity().Size() > 1.0f ? MyPlayerAnimState::JOG_FWD : MyPlayerAnimState::IDLE;
}

