// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../../Monster/Character/NormalMonster.h"
#include "../../Monster/AI/AICon_NormalMonster.h"
#include "../../Monster/Data/NormalMonsterState.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_MoveToPatrol::UBTTask_MoveToPatrol()
{
	
}

EBTNodeResult::Type UBTTask_MoveToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::PATROL);

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetNormalMonster(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 150.0f;
	}

	return Result;
}

UBlackboardComponent* UBTTask_MoveToPatrol::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	return Blackboard;
}

ANormalMonster* UBTTask_MoveToPatrol::GetNormalMonster(UBehaviorTreeComponent& OwnerComp)
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
