// Fill out your copyright notice in the Description page of Project Settings.


#include "AICon_NormalMonster.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/AINormalMonster.h"


AAICon_NormalMonster::AAICon_NormalMonster()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BEHAVIORTREECOMPONENT"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BLACKBOARDCOMPONENT"));
}

void AAICon_NormalMonster::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	if (nullptr != BehaviorTreeComp && BehaviorTreeComp->IsValidLowLevel() == true)
	{
		int a = 0;


		/*
		AAINormalMonster* AIPawn = Cast<AAINormalMonster>(_Pawn);
		UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();
		BehaviorTreeComp->StartTree(*BehaviorTree);
		*/
	}
}
