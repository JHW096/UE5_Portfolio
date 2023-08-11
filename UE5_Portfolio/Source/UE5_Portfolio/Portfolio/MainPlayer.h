// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Global/MainPlayerAnimState.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class UE5_PORTFOLIO_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const
	{
		return TopDownCameraComponent;
	}
	
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const
	{
		return SpringArmComponent;
	}

private: 

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* OpacityMaterial;

	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* NoneOpacityMaterial;

	TArray<UPrimitiveComponent*> PrevComponents;

public:

	void MoveAction();
	void NormalAttackAction();

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	PlayerAnimState AnimState;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	TMap<PlayerAnimState, UAnimMontage*> AllAnimations;


	////-----------col test

public:

	UFUNCTION()
	void BeginOverLap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
