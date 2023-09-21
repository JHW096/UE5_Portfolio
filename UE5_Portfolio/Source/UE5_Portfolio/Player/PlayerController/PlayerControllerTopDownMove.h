// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerBase.h"
#include "PlayerControllerTopDownMove.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APlayerControllerTopDownMove : public APlayerControllerBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

protected:
	
	virtual void BeginPlay() override;

	virtual void PlayerTick(float _DeltaSeconds) override;

	virtual void SetupInputComponent() override;
	
public:
	
	
	FORCEINLINE FHitResult GetCursorHitResult() const
	{
		return m_CursorHitResult;
	}

	FORCEINLINE FVector GetCachedDestination() const
	{
		return CachedDestination;
	}

	FORCEINLINE void SetCacheDestination(FVector _Val)
	{
		CachedDestination = _Val;
	}

public:

	bool HitSucceeded();

	//CursorMovementFunction
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	
	
	//void GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

private:

	//Movment Value
	FHitResult m_CursorHitResult;
	FVector CachedDestination;
	float FollowTime;

};
