// Fill out your copyright notice in the Description page of Project Settings.


#include "AINormalMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AI/AICon_NormalMonster.h"


UBlackboardComponent* AAINormalMonster::GetBlackboardComp()
{
	if (BlackboardComp == nullptr)
	{
		AAICon_NormalMonster* AICon_NormalMonster = GetController<AAICon_NormalMonster>();

		if (AICon_NormalMonster == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("%s(%u) : AINormalMonster : NormalMonsterAI is nullptr"), __FUNCTION__, __LINE__);
			return nullptr;
		}
		//GetBlackboardComponent는 AAIContorller에 있음.
		BlackboardComp = AICon_NormalMonster->GetBlackboardComponent();
	}

	return BlackboardComp;
}
