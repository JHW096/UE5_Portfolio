// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../Data/NormalMonsterData.h"
#include "../../Global/TopDownGameInstance.h"

AMeleeMonster::AMeleeMonster()
{
		
}

void AMeleeMonster::BeginPlay()
{
	UTopDownGameInstance* GameInstance = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInstance != nullptr)
	{
		NormalMonsterData = GameInstance->GetNormalMonsterData(MeleeMonsterName);

		for (TPair<NormalMonsterState, UAnimMontage*> pair : NormalMonsterData->NormalMonsterAnims)
		{
			PushAnimation(pair.Key, pair.Value);
		}
	}
}
