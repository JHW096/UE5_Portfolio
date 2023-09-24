// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerTopDownMove.h"
#include "PlayerControllerBattleItemBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APlayerControllerBattleItemBase : public APlayerControllerTopDownMove
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FristBattleItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SecondBattleItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThirdBattleItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ForthBattleItemKey;

protected:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float _DeltaSeconds) override;

	virtual void SetupInputComponent() override;
	

public:

	//BattleItem First slot Press Start
	void OnFristStart();


};
