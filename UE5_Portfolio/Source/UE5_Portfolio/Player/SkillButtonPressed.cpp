// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillButtonPressed.h"
#include "../Portfolio/PortfolioPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASkillButtonPressed::ASkillButtonPressed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillButtonPressed::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APortfolioPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController == nullptr)
	{
		int a = 0;
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : PlayerController == nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	

}

// Called every frame
void ASkillButtonPressed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	PlayerHitResult = PlayerController->GetHitResult();

	bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, PlayerHitResult);
	if (bHitSuccessful)
	{
		SetActorLocation(PlayerHitResult.Location);
	}

}

