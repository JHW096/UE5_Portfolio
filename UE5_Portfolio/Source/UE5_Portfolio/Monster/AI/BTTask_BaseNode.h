// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BaseNode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UBTTask_BaseNode : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public: 

	UBTTask_BaseNode();

	void OnGameplayTaskActivated(class UGameplayTask&) override;

};
