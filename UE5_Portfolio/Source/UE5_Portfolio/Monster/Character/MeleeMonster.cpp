// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../../Global/TopDownGameInstance.h"
#include "../Data/MonsterData.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	GetBlackboardComp()->SetValueAsEnum(TEXT("NormalMonsterState"), static_cast<uint8>(NormalMonsterState::IDLE));
	GetBlackboardComp()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComp()->SetValueAsFloat(TEXT("SearchRange"), NormalMonsterData->SearchRange);
	GetBlackboardComp()->SetValueAsFloat(TEXT("AttackRange"), NormalMonsterData->AttackRange);
	GetBlackboardComp()->SetValueAsVector(TEXT("SpawnPos"), SpawnPos);
	GetBlackboardComp()->SetValueAsFloat(TEXT("RangeOver"), NormalMonsterData->RangeOver);
}
