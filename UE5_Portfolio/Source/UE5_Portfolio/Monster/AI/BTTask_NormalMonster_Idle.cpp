// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Idle.h"
#include "../Character/NormalMonster.h"
#include "AICon_NormalMonster.h"
#include "../Data/NormalMonsterState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalMonster_Idle::UBTTask_NormalMonster_Idle()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_NormalMonster_Idle::OnGameplayTaskActivated(UGameplayTask&)
{
	
}

EBTNodeResult::Type UBTTask_NormalMonster_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	return;
}
