// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerTopDownMove.h"
#include "PlayerControllerGreatSword.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APlayerControllerGreatSword : public APlayerControllerTopDownMove
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InputCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InputQAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InputWAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InputEAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InputRAction;


protected:

	APlayerControllerGreatSword();

	virtual void BeginPlay() override;

	virtual void PlayerTick(float _DeltaSeconds) override;

	virtual void SetupInputComponent() override;


public:

	void InputCKeyStart();

	void InputQKeyStart();

	void InputWKeyStart();

	void InputEKeyStart();

	void InputRKeyStart();
	void InputRKeyTriggered();

private:

	class AGreatSwordCharacter* m_Player = nullptr;

};
