// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../Data/NormalMonsterData.h"
#include "../../Global/TopDownGameInstance.h"

AMeleeMonster::AMeleeMonster()
{
	UTopDownGameInstance* GameInstance = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInstance != nullptr)
	{
		NormalMonsterData;
	}
}
