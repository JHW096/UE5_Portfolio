// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class NormalMonsterState : uint8
{
	NONE,
	IDLE,
	MOVE,
	RETURN,
	PATROL,
	ATTACK,
	HIT,
	DEATH
};