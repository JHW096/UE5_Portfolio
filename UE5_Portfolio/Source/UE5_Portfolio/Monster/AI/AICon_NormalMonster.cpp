// Fill out your copyright notice in the Description page of Project Settings.


#include "AICon_NormalMonster.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
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
		AAINormalMonster* AIMonster = Cast<AAINormalMonster>(_Pawn);

		if (AIMonster == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("%s(%u) AIController : Failed to Cast AINormalMonster"), __FUNCTION__, __LINE__);
			return;
		}

		UBehaviorTree* BehaviorTree = AIMonster->GetBehaviorTree();

		if (BehaviorTree == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("%s(%u) AIController : Failed to Get BehaviorTree"), __FUNCTION__, __LINE__);
			return;
		}

		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		
		BlackboardComp->SetValueAsObject(TEXT("SelfActor"), _Pawn);

		BehaviorTreeComp->StartTree(*BehaviorTree);

	}
}
