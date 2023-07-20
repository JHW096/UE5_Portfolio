// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../Data/NormalMonsterData.h"
#include "../../Global/TopDownGameInstance.h"
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

	GetBlackboardComp()->SetValueAsEnum(TEXT("NormalMonsterState"), static_cast<uint8>(NormalMonsterState::IDLE));
	int a = 0;
	/*GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), NormalMonsterData->SearchRange);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), NormalMonsterData->AttackRagne);*/
}
