// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownMoveCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATopDownMoveCharacterBase::ATopDownMoveCharacterBase()
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

}

// Called when the game starts or when spawned
void ATopDownMoveCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownMoveCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CoverObjectDownOpacity();

}

// Called to bind functionality to input
void ATopDownMoveCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATopDownMoveCharacterBase::CoverObjectDownOpacity()
{
	TArray<FHitResult> OutHits;
	FVector Start = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()); // Line start
	FVector End = GetActorLocation() + FVector(-500.0f, 0.0f, 500.0f);
	FName ProfileName = TEXT("CoverToPlayer");
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);

	FHitResult hit;
	TArray<UPrimitiveComponent*> CurComponents;

	if (OutHits.Num() != 0)
	{
		for (size_t i = 0; i < OutHits.Num(); i++)
		{
			CurComponents.Add(OutHits[i].GetComponent());
		}
	}

	for (size_t i = 0; i < PrevComponents.Num(); i++)
	{
		if (CurComponents.Contains(PrevComponents[i]) == false)
		{
			PrevComponents[i]->SetMaterial(0, NoneOpacityMaterial);
			PrevComponents.RemoveAt(i);
			--i;
		}
	}

	for (size_t i = 0; i < CurComponents.Num(); i++)
	{
		if (PrevComponents.Contains(CurComponents[i]) == false)
		{
			CurComponents[i]->SetMaterial(0, OpacityMaterial);
			PrevComponents.Add(CurComponents[i]);
		}
	}
}

