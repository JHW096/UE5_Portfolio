// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputSpaceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputCKeyAction;

protected:

	uint32 bMoveToMouseCursor : 1;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	//virtual void PlayerTick(float _DeltaSeconds) override;
	

public:

	//PLAYER_MOVE
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	//PLAYER_DASH
	void OnInputSpaceKeyPressed();

	//PLAYER_GUN_NORMAL_ATTACK(TEMP)
	void OnInputCKeyPressed();

private:

	//Mouse Cursor Hit
	FHitResult m_HitResult;

	//Chracter
	class APlayerCharacter* Player;

	//Movement
	FVector CachedDestination;
	float FollowTime;	

};
