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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputQKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputWKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputEKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputRKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputLMouseAction;


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

	//PLAYER_NORMAL_ATTACK_SWORD(TEMP)
	void OnInputQKeyPressed();

	//PLAYER_SECOND_SKILL_PRESSED
	UFUNCTION(BlueprintCallable)
	void OnInputWKeyPressed();
	void OnInputWKeyTriggered();
	void OnInputWKeyCanceled();

	//PLAYER_E_KEY_
	void OnInputEKeyPressed();

	//PLAYER_R_KEY_RELATE
	void OnInputRKeyPressed();
	void OnInputRKeyReleased();

	//PLAYER_R_MOUSE_BUTTON_
	void OnMouseLButtonClicked();
	

public:

	UFUNCTION(BlueprintCallable)
	void OnShootNotify();


public:

	FORCEINLINE FHitResult GetHitResult()
	{
		return m_HitResult;
	}

	FORCEINLINE FVector GetChacheDestination()
	{
		return CachedDestination;
	}

public:

	FORCEINLINE void SetChacheDestination(const FVector& _Vec)
	{
		CachedDestination = _Vec;
	}

private:


private:

	//Mouse Cursor Hit
	FHitResult m_HitResult;

	//Chracter
	class APlayerCharacter* Player;

	class UMyAnimInstance* m_AnimInstance;

	//Movement
	FVector CachedDestination;
	float FollowTime;	

	class AActor* Bullet = nullptr;

private:

	//���߿� Array�� ���� DataTable�̶� ����.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_Bullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_CrossHairActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_SnipeShootActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_AreaShot;


	class UMainWidget* m_MainWidget = nullptr;
};
