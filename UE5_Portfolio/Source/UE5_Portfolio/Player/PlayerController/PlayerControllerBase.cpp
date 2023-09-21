// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(m_DefaultMappingContext, 0);
	}
}

void APlayerControllerBase::PlayerTick(float _DeltaSeconds)
{
	Super::PlayerTick(_DeltaSeconds);
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (!EnhancedInputComponent)
	{
		return;
	}

}

UInputMappingContext* APlayerControllerBase::GetMappingContext()
{
	return m_DefaultMappingContext;
}

void APlayerControllerBase::SetMappingContext(UInputMappingContext* p_MappingContext)
{
	m_DefaultMappingContext = p_MappingContext;

	if (m_DefaultMappingContext == nullptr)
	{
		//Log
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) MappingContext == Nullptr"), __FUNCTION__, __LINE__);
		m_DefaultMappingContext = nullptr;
		return;
	}
}

UInputAction* APlayerControllerBase::GetInputActionFromName(const FName& _Name)
{
	return *m_InputActionMap.Find(_Name);
}

void APlayerControllerBase::AddInputAction(FName _Name, class UInputAction* p_InputAction)
{
	if (!InputActionNameCheck(_Name))
	{
		return;
	}
	//Virtual Function
}

TMap<FName, class UInputAction*> APlayerControllerBase::GetAllInputAction()
{
	return m_InputActionMap;
}

bool APlayerControllerBase::InputActionNameCheck(FName _Name)
{
	for (auto& InputAction : m_InputActionMap)
	{
		if (InputAction.Key == _Name)
		{
			return false;
		}
	}
	
	return true;
}
