// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BaseNode.h"

UBTTask_BaseNode::UBTTask_BaseNode()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_BaseNode::OnGameplayTaskActivated(UGameplayTask&)
{
}

