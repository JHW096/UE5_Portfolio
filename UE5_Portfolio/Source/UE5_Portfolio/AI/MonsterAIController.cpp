// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"




AMonsterAIController::AMonsterAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BEHAVIORCOMPONENT"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BLACKBOARDCOMPONENT"));

	
}

void AMonsterAIController::OnPossess(APawn* _Pawn)
{
	if (_Pawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) MonsterAIController can not access Pawn"), __FUNCTION__, __LINE__);
		return;
	}


	Super::OnPossess(_Pawn);

	if (BehaviorTreeComponent != nullptr && BehaviorTreeComponent->IsValidLowLevel() == true)
	{
		int a = 0;
	}
}