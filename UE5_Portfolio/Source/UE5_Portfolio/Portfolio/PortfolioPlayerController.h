// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PortfolioPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APortfolioPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APortfolioPlayerController();

public:
	//short press value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	//NormalAttack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputCButtonAction;
	
	//TestUI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputGButtonAction;

	//Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputIButtonAction;

	//QSkill
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputQButtonAction;

	//WSkill
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputWButtonAction;


public:

	FORCEINLINE float GetChargeTime()
	{
		return ChargeTime;
	}

	FORCEINLINE void ResetChargeTime()
	{
		ChargeTime = 0.0f;
	}

protected:
	uint32 bMoveToMouseCursor : 1;

	//Override
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void PlayerTick(float _DeltaSeconds) override;

	//Mouse Move
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();


	//Attack
	void OnInputCKeyPressed();
	void OnInputCKeyReleased();

	//Skill_Q
	void OnInputQKeyPressed();
	void OnInputQKeyTriggered();
	void OnInputQKeyReleased();
	void OnInputQKeyCanceled();


	//Skill_W
	void OnInputWKeyPressed();


	//UI
	void OnInputTestUIKeyPressed();
	void OnInputIKeyPressed();


private:

	FVector CachedDestination;

	float FollowTime;	//How long it has been pressed

	class AMainPlayer* MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> tmp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Skill_W;

	AActor* skill = nullptr;
	float ChargeTime;



	FVector CursorLocation;


};
