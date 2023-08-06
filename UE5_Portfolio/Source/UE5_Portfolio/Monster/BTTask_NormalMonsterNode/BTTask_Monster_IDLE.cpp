// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_IDLE.h"
#include "../../Global/TopDownGameInstance.h"



UBTTask_Monster_IDLE::UBTTask_Monster_IDLE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	
}

EBTNodeResult::Type UBTTask_Monster_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::IDLE);

	return EBTNodeResult::InProgress;
}

void UBTTask_Monster_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	/*int PatrolTime = UTopDownGameInstance::MainRandom.RandRange(0, 3);

	if (GetStateTime(OwnerComp) >= PatrolTime)
	{
		SetNormalMonsterState(OwnerComp, NormalMonsterState::PATROL);
		return; 
	}*/

	if (GetStateTime(OwnerComp) >= 3.0f)
	{
		ResetStateTime(OwnerComp);

		SetNormalMonsterState(OwnerComp, NormalMonsterState::PATROL);
		return;
	}


	AActor* TargetActor = GetTargetSearch(OwnerComp);

	if (TargetActor != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetActor);
		SetNormalMonsterState(OwnerComp, NormalMonsterState::MOVE);
		return;
	}

	return;
}
