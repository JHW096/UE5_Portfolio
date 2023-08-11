// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../../Global/TopDownGameInstance.h"
#include "../Data/MonsterData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

AMeleeMonster::AMeleeMonster()
{
		
}

void AMeleeMonster::BeginPlay()
{
	UTopDownGameInstance* GameInstance = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInstance != nullptr)
	{
		NormalMonsterData = GameInstance->GetNormalMonsterData(MeleeMonsterName);

		for (TPair<NormalMonsterState, UAnimMontage*> pair : NormalMonsterData->NormalMonsterAnims)
		{
			PushAnimation(pair.Key, pair.Value);
		}
		SetAnimState(NormalMonsterState::IDLE);
	}

	Super::BeginPlay();

	FVector SpawnPos = GetActorLocation();

#pragma region SetBlackBoard

	GetBlackboardComp()->SetValueAsEnum(TEXT("NormalMonsterState"), static_cast<uint8>(NormalMonsterState::IDLE));
	GetBlackboardComp()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComp()->SetValueAsFloat(TEXT("SearchRange"), NormalMonsterData->SearchRange);
	GetBlackboardComp()->SetValueAsFloat(TEXT("AttackRange"), NormalMonsterData->AttackRange);
	GetBlackboardComp()->SetValueAsVector(TEXT("SpawnPos"), SpawnPos);
	GetBlackboardComp()->SetValueAsFloat(TEXT("RangeOver"), NormalMonsterData->RangeOver);

#pragma endregion 

#pragma region Delegate

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonster::BeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMeleeMonster::OnHit);
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonster::BeginOverlap);
	GetMesh()->OnComponentHit.AddDynamic(this, &AMeleeMonster::OnHit);

#pragma endregion



}

void AMeleeMonster::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("MeteoEnd")))
	{
		this->Destroy();
		OtherActor->Destroy();
		
	}
}
void AMeleeMonster::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("FirstSkill")))
	{
		//OtherActor->Destroy();
	}
}

