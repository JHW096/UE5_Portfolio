// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICon_NormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AAICon_NormalMonster : public AAIController
{
	GENERATED_BODY()
	
public:

	AAICon_NormalMonster();

protected:

	void OnPossess(APawn* _Pawn) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComp;

};
