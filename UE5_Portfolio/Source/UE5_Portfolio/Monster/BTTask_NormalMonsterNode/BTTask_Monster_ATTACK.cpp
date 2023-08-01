// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_ATTACK.h"

UBTTask_Monster_ATTACK::UBTTask_Monster_ATTACK()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Monster_ATTACK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(UBTTask_NormalMonsterBaseNode::GetNormalMonsterState(OwnerComp));

	return EBTNodeResult::InProgress;
}

void UBTTask_Monster_ATTACK::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	UAnimMontage* Montage = GetNormalMonster(OwnerComp)->GetAnimMontage(UBTTask_NormalMonsterBaseNode::GetNormalMonsterState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();

	if (Time <= GetStateTime(OwnerComp))
	{
		SetNormalMonsterState(OwnerComp, NormalMonsterState::MOVE);
	}
	
}
