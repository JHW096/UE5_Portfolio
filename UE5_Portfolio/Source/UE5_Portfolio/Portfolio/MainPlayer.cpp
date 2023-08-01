// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Global/TopDownGameInstance.h"
#include "Components/MeshComponent.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
	
	// Do not Rotate Character to Camera direction
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}
	
	//Configure Character Movement
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
	}
	

	// Create SpringArm
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
		SpringArmComponent->SetupAttachment(RootComponent);
		SpringArmComponent->SetUsingAbsoluteRotation(true); //Don't want arm to rotate when character does
		SpringArmComponent->TargetArmLength = 1250.0f;
		SpringArmComponent->SetRelativeRotation(FRotator(-50.0f, 0.0f, 0.0f));
		SpringArmComponent->bDoCollisionTest = false; // Don't want ot pull camera in when it collides with level
	}
	
	
	

	//Create Camera
	{
		TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TOPDOWNCAMERA"));
		TopDownCameraComponent->SetupAttachment(SpringArmComponent);
		TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotaterelative to arm
	}
	
	

	//SetSkeletalMesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(
			TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'")
		);

		if (SkelMesh.Succeeded())
		{
			GetMesh()->SetSkeletalMesh(SkelMesh.Object);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s(%u) MainPlayer : Can not found Skeletal Mesh"), __FUNCTION__, __LINE__);
		}
	}

	AnimState = PlayerAnimState::IDLE;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::BeginOverLap);
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAction();

	TArray<FHitResult> OutHits;
	FVector Start = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()); // Line start
	FVector End = GetActorLocation() + FVector(-500.0f, 0.0f, 500.0f);
	FName ProfileName = TEXT("CoverToPlayer");
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);

	if (OutHits.Num() != 0)
	{
		int a = 0;
	}

}

void AMainPlayer::MoveAction()
{
	if (AnimState == PlayerAnimState::NORMAL_ATTACK)
	{
		return;
	}
	AnimState = GetVelocity().Size() > 1.0f ? PlayerAnimState::JOG_FWD : PlayerAnimState::IDLE;
}

void AMainPlayer::NormalAttackAction()
{
	
	AnimState = PlayerAnimState::NORMAL_ATTACK;
}

void AMainPlayer::BeginOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{

	if (OtherActor->ActorHasTag(TEXT("Item")))
	{
		OtherActor->Destroy();
	}

	
	
}


