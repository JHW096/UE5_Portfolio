// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownMoveCharacterBase.generated.h"

UCLASS()
class UE5_PORTFOLIO_API ATopDownMoveCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownMoveCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void CoverObjectDownOpacity();

public:

	FORCEINLINE class USpringArmComponent* GetSpringArmComponenet() const
	{
		return m_SpringArmComponent;
	}

	FORCEINLINE class UCameraComponent* GetCameraComponent() const
	{
		return m_CameraComponent;
	}

private:

	UPROPERTY(Category = "SpringArmComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* m_SpringArmComponent;

	UPROPERTY(Category = "CameraComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* m_CameraComponent;


private:

	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMaterialInterface* OpacityMaterial;

	UPROPERTY(Category = "Material", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMaterialInterface* NoneOpacityMaterial;

	TArray<UPrimitiveComponent*> PrevComponents;
};
