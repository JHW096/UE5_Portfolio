// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchRangeOver.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTService_SearchRangeOver : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SearchRangeOver();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	class ANormalMonster* GetNormalMonster(UBehaviorTreeComponent& OwnerComp);

	UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp);

	AActor* GetTargetSearch(UBehaviorTreeComponent& OwnerComp);
	
};
