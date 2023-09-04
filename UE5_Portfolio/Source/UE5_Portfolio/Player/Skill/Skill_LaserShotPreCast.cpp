// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_LaserShotPreCast.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/PlayerCharacter.h"

// Sets default values
ASkill_LaserShotPreCast::ASkill_LaserShotPreCast()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_LaserShotPreCast::BeginPlay()
{
	Super::BeginPlay();
	
	OnDestroyed.AddDynamic(this, &ASkill_LaserShotPreCast::OnActorDestroy);
}

// Called every frame
void ASkill_LaserShotPreCast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->StopMovement();
}

void ASkill_LaserShotPreCast::OnActorDestroy(AActor* _Destroy)
{

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); 
	FTransform SpawnTransform;

	SpawnTransform = Player->GetMesh()->GetSocketTransform(TEXT("WP_Gun_Socket"));
	SpawnTransform.SetRotation(Player->GetActorForwardVector().Rotation().Quaternion());

	GetWorld()->SpawnActor<AActor>(m_NextActor, SpawnTransform);
}



