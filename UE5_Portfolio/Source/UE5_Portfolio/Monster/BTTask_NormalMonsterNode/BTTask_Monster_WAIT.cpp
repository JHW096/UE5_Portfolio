// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_WAIT.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../../Monster/Character/NormalMonster.h"
#include "../../Monster/AI/AICon_NormalMonster.h"
#include "../../Monster/Data/NormalMonsterState.h"

UBTTask_Monster_WAIT::UBTTask_Monster_WAIT()
{

}

EBTNodeResult::Type UBTTask_Monster_WAIT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::IDLE);

	return Result;
}

UBlackboardComponent* UBTTask_Monster_WAIT::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	return Blackboard;
}

ANormalMonster* UBTTask_Monster_WAIT::GetNormalMonster(UBehaviorTreeComponent& OwnerComp)
{
	AAICon_NormalMonster* AI_Controller = GetBlackboardComponent(OwnerComp)->GetOwner<AAICon_NormalMonster>();
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
