// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_AreaShotStart.generated.h"

UCLASS()
class UE5_PORTFOLIO_API ASkill_AreaShotStart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkill_AreaShotStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		FORCEINLINE FVector GetLocation() const
	{
		return m_EndLocation;
	}

private:

	class AMyPlayerController* m_PlayerController = nullptr;

	UPROPERTY(Category = "Transform", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector m_EndLocation;


};