// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../Data/NormalMonsterState.h"
#include "AICon_NormalMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/NormalMonster.h"
#include "BTTask_BaseNode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_BaseNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:


public: 

	UBTTask_BaseNode();

	//Essential Override
	void OnGameplayTaskActivated(class UGameplayTask&) override;

public:
	//Releated TaskNode Function
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds) override;

public:
	//Getter

	class ANormalMonster* GetNormalMonster(UBehaviorTreeComponent& OwnerComp);

	class UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);
	
	NormalMonsterState GetNormalMonsterState(UBehaviorTreeComponent& OwnerComp);

public:
	//StateTime Fucntions.

	float GetStateTime(UBehaviorTreeComponent& OwnerComp);

	void ResetStateTime(UBehaviorTreeComponent& OwnerComp);


public: 
	//StateChange Functions.

	template<typename EnumType> 
	void SetStateChange(UBehaviorTreeComponent& OwnerComp, EnumType State);

	void SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 State);



};

template<typename EnumType>
inline void UBTTask_BaseNode::SetStateChange(UBehaviorTreeComponent& OwnerComp, EnumType State)
{
	SetStateChange(OwnerComp, static_cast<uint8>(State));
}
