// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../PlayerAnimState.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE5_PORTFOLIO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(Category = "Animation_Value", EditAnywhere, BlueprintReadWrite)
	float testtime = 0.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void MoveAction();

public:
	
	void UncoverPlayer();

public:

	FORCEINLINE class USpringArmComponent* GetSpringArmComponenet() const
	{
		return m_SpringArmComponent;
	}

	FORCEINLINE class UCameraComponent* GetCameraComponent() const
	{
		return m_CameraComponent;
	}

	FORCEINLINE UAnimMontage* GetAnimMontage(MyPlayerAnimState _AnimState)
	{
		return AllAnimations[_AnimState];
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UPlayerStatComponent* GetPlayerStatComponent()
	{
		return m_PlayerStatComponent;
	}

public:

	UPROPERTY(Category = "Animation_Value", EditAnywhere, BlueprintReadWrite)
	MyPlayerAnimState m_AnimState;

	class AMyPlayerController* m_PlayerController = nullptr;

	UPROPERTY(Category = "Animation_Value", EditAnywhere, BlueprintReadWrite)
	TMap<MyPlayerAnimState, UAnimMontage*> AllAnimations;

private:

	UPROPERTY(Category = "SpringArmComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_SpringArmComponent;

	UPROPERTY(Category = "CameraComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class UPlayerStatComponent* m_PlayerStatComponent;

private: 

	//BEHIND PLAYER
	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* OpacityMaterial;

	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* NoneOpacityMaterial;

	TArray<UPrimitiveComponent*> PrevComponents;

	float DestroyDistance = 0.0f;

	class AActor* m_Bullet;
};
