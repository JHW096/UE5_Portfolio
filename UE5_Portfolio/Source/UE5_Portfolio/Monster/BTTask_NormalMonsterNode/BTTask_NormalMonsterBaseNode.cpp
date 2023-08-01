// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonsterBaseNode.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalMonsterBaseNode::UBTTask_NormalMonsterBaseNode()
{
	//This val make this tick fucntion.
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_NormalMonsterBaseNode::OnGameplayTaskActivated(UGameplayTask&)
{
}

EBTNodeResult::Type UBTTask_NormalMonsterBaseNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_NormalMonsterBaseNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : Blackboard is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	float StateTime = Blackboard->GetValueAsFloat(TEXT("StateTime"));
	StateTime += DelataSeconds;
	Blackboard->SetValueAsFloat(TEXT("StateTime"), StateTime);


	bool IsHitted = Blackboard->GetValueAsBool(TEXT("IsHitted"));

	if ((GetNormalMonsterState(OwnerComp) != NormalMonsterState::DEATH) && (GetNormalMonsterState(OwnerComp) != NormalMonsterState::RETURN))
	{
		if (IsHitted)
		{
			SetNormalMonsterState(OwnerComp, NormalMonsterState::DEATH);
			return;
		}
	}
}

ANormalMonster* UBTTask_NormalMonsterBaseNode::GetNormalMonster(UBehaviorTreeComponent& OwnerComp)
{
	AAICon_NormalMonster* AI_Controller = OwnerComp.GetOwner<AAICon_NormalMonster>();
	if (AI_Controller == nullptr || AI_Controller->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterAIController is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ANormalMonster* NormalMonsterPawn = AI_Controller->GetPawn<ANormalMonster>();
	if (NormalMonsterPawn == nullptr || NormalMonsterPawn->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterPawn is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return NormalMonsterPawn;
}

UBlackboardComponent* UBTTask_NormalMonsterBaseNode::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	return Blackboard;
}

NormalMonsterState UBTTask_NormalMonsterBaseNode::GetNormalMonsterState(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return NormalMonsterState::NONE;
	}

	uint8 Enum = Blackboard->GetValueAsEnum(TEXT("NormalMonsterState"));

	return static_cast<NormalMonsterState>(Enum);
}

AActor* UBTTask_NormalMonsterBaseNode::GetTargetSearch(UBehaviorTreeComponent& OwnerComp)
{
	AActor* FindTarget = nullptr;

	FString TargetTag = OwnerComp.GetBlackboardComponent()->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	ANormalMonster* OwnerActor = GetNormalMonster(OwnerComp);

	float SearchRagne = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("SearchRange"));

	if (TargetActors.Num() != 0)
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Distance = (OwnerActor->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRagne <= Distance)
			{
				continue;
			}

			if (Range > Distance)
			{
				Range = Distance;
				FindTarget = TargetActors[i];
			}
		}
	}

	return FindTarget;
}

float UBTTask_NormalMonsterBaseNode::GetStateTime(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return 0.0f;
	}

	float StateTime = Blackboard->GetValueAsFloat(TEXT("StateTime"));

	return StateTime;
}

void UBTTask_NormalMonsterBaseNode::ResetStateTime(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	Blackboard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}

void UBTTask_NormalMonsterBaseNode::SetNormalMonsterState(UBehaviorTreeComponent& OwnerComp, uint8 State)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	Blackboard->SetValueAsEnum(TEXT("NormalMonsterState"), State);

	ResetStateTime(OwnerComp);

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
}
