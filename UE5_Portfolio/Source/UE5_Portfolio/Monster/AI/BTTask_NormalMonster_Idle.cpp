// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Idle.h"
#include "../Character/NormalMonster.h"
#include "AICon_NormalMonster.h"
#include "../Data/NormalMonsterState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/NumericLimits.h"

UBTTask_NormalMonster_Idle::UBTTask_NormalMonster_Idle()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NormalMonster_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::IDLE);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//추적
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	int a = 0;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s, %u : Blackboard is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	FString TargetTag = Blackboard->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);
	

	ANormalMonster* ThisMonster = GetNormalMonster(OwnerComp);
	float SearchRagne = Blackboard->GetValueAsFloat(TEXT("SearchRange"));


	if (TargetActors.Num() != 0)
	{
		AActor* TargetAggro = nullptr; 
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Distance = (ThisMonster->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRagne <= Distance)
			{
				continue;
			}

			//가장 가까운 거리의 Player Actor를 찾는 과정
			if (Range > Distance)
			{
				Range = Distance;
				TargetAggro = TargetActors[i];
			}
		}

		if (TargetAggro != nullptr)
		{
			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), TargetAggro);	
			SetStateChange(OwnerComp, NormalMonsterState::MOVE);
			return;
		}
	}


	return;
}
