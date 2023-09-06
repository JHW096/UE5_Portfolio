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
	class UInputAction* InputFKeyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputLMouseAction;


	//Inven Onff
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InputIKeyAction;



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

	//PLAYER_F_KEY_
	void OnInputFKeyPressed();

	//PLAYER_I_KEY
	void OnInputIKeyPressed();


	//PLAYER_R_MOUSE_BUTTON_
	void OnMouseLButtonClicked();
	

public:

	UFUNCTION(BlueprintCallable)
	void OnShootNotify();

	UFUNCTION(BlueprintCallable)
	void AreaShotDecalDestroyed();

public:

	UFUNCTION(BlueprintCallable)
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

	//³ªÁß¿¡ Array·Î ¹­ÀÚ DataTableÀÌ¶û °°ÀÌ.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_Bullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_CrossHairActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_SnipeShootActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_AreaShotDecal;

	AActor* m_DecalActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_AreaShotStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_AreaShotEnd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_LaserShotStart;

	bool m_OnArea = false;

	class UMainWidget* m_MainWidget = nullptr;

	FVector2D CrossHairWidgetScale = { 5.0, 5.0 };

public:

	
	FORCEINLINE TSubclassOf<AActor> GetLaserShotStart()
	{
		return m_LaserShotStart;
	}
	

	FORCEINLINE void SetOnArea(bool _bool)
	{
		m_OnArea = _bool;
	}
};
