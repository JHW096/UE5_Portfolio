// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class MyPlayerAnimState : uint8
{
	NONE,
	IDLE,
	JOG_FWD,
	DASH,
	NORMAL_ATTACK_GUN,
	NORMAL_ATTACK_SWORD,
	SKILL_W,
	SNIPE_SHOOT,
	SKILL_E,
	SKILL_F
};


UENUM(BlueprintType)
enum class GreatSwordAnimState : uint8
{
	NONE,
	IDLE,
	JOG_FWD,
	DASH,
	CKey,
	QKey,
	WKey,
	EKey,
	RKey
};