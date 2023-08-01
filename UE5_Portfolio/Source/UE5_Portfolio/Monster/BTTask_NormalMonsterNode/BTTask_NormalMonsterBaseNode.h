// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../AI/AICon_NormalMonster.h"
#include "../Data/NormalMonsterState.h"
#include "../Character/NormalMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_NormalMonsterBaseNode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_NormalMonsterBaseNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:

public:

	UBTTask_NormalMonsterBaseNode();

	//ÇÊ¼ö Override 
	void OnGameplayTaskActivated(class UGameplayTask&) override;

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds) override;

public:

	class ANormalMonster* GetNormalMonster(UBehaviorTreeComponent& OwnerComp);

	class UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);

	NormalMonsterState GetNormalMonsterState(UBehaviorTreeComponent& OwnerComp);

	class AActor* GetTargetSearch(UBehaviorTreeComponent& OwnerComp);

public:
	//Time Section
	float GetStateTime(UBehaviorTreeComponent& OwnerComp);

	void ResetStateTime(UBehaviorTreeComponent& OwnerComp);

public:
	//SetState Section
	
	template<typename EnumType>
	void SetNormalMonsterState(UBehaviorTreeComponent& OwnerComp, EnumType State);

	void SetNormalMonsterState(UBehaviorTreeComponent& OwnerComp, uint8 State);

};

template<typename EnumType>
inline void UBTTask_NormalMonsterBaseNode::SetNormalMonsterState(UBehaviorTreeComponent& OwnerComp, EnumType State)
{
	SetNormalMonsterState(OwnerComp, static_cast<uint8>(State));
}
