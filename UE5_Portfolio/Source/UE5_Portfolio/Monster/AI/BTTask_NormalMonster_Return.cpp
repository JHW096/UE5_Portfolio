// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Return.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalMonster_Return::UBTTask_NormalMonster_Return()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_NormalMonster_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Animation -> Normal
	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::RETURN);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector ThisPos = GetNormalMonster(OwnerComp)->GetActorLocation();
	ThisPos.Z = 0.0f;
	FVector Dir = OriginPos - ThisPos;
	
	int a = 0;

	GetNormalMonster(OwnerComp)->AddMovementInput(Dir);

	if (ThisPos == OriginPos)
	{
		SetStateChange(OwnerComp, NormalMonsterState::IDLE);
	}
	
}
