// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Attack.h"

UBTTask_NormalMonster_Attack::UBTTask_NormalMonster_Attack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NormalMonster_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(UBTTask_BaseNode::GetNormalMonsterState(OwnerComp));

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UAnimMontage* Montage = GetNormalMonster(OwnerComp)->GetAnimMontage(UBTTask_BaseNode::GetNormalMonsterState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();

	int a = 0;

	if (Time <= GetStateTime(OwnerComp))
	{
		SetStateChange(OwnerComp, NormalMonsterState::MOVE);
	}

}
