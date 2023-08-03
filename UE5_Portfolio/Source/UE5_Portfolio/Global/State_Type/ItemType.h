// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class ItemType : uint8
{
	NONE,
	WEAPON,
	ARMOR,
	POSTION,
	QUEST, 
	BATTLEITEM,
	NORMAL,
};