// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "ControllerUI.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AControllerUI : public AMyPlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float _DeltaSeconds) override;

public:

	void RKeyPressedUI();
	
};
