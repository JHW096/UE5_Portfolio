// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BaseNode.h"


UBTTask_BaseNode::UBTTask_BaseNode()
{
	//This val make this tick fucntion.
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

//Essential override fucntion
void UBTTask_BaseNode::OnGameplayTaskActivated(UGameplayTask&)
{
}

EBTNodeResult::Type UBTTask_BaseNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_BaseNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
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

}



ANormalMonster* UBTTask_BaseNode::GetNormalMonster(UBehaviorTreeComponent& OwnerComp)
{
	AAICon_NormalMonster* AIController = OwnerComp.GetOwner<AAICon_NormalMonster>();
	if (AIController == nullptr || AIController->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterAIController is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ANormalMonster* MonsterPawn = AIController->GetPawn<ANormalMonster>();
	if (MonsterPawn == nullptr || MonsterPawn->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterPawn is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}


	return MonsterPawn;
}

UBlackboardComponent* UBTTask_BaseNode::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Blackboard; 
}

NormalMonsterState UBTTask_BaseNode::GetNormalMonsterState(UBehaviorTreeComponent& OwnerComp)
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






float UBTTask_BaseNode::GetStateTime(UBehaviorTreeComponent& OwnerComp)
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

void UBTTask_BaseNode::ResetStateTime(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	Blackboard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}





void UBTTask_BaseNode::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 State)
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


