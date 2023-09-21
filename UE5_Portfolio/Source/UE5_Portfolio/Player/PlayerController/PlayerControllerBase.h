// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float _DeltaSeconds) override;

	virtual void SetupInputComponent() override;

public:


	class UInputMappingContext* GetMappingContext();

	void SetMappingContext(class UInputMappingContext* p_MappingContext);
	
	class UInputAction* GetInputActionFromName(const FName& _Name);

	virtual void AddInputAction(FName _Name, class UInputAction* p_InputAction);

	TMap<FName, class UInputAction*> GetAllInputAction();

	bool InputActionNameCheck(FName _Name);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* m_DefaultMappingContext;

	TMap<FName, class UInputAction*> m_InputActionMap;

	UEnhancedInputComponent* EnhancedInputComponent;

};
