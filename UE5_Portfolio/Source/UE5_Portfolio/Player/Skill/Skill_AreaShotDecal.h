// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "Skill_AreaShotDecal.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API ASkill_AreaShotDecal : public ADecalActor
{
	GENERATED_BODY()
	
protected:

	ASkill_AreaShotDecal();

	virtual void BeginPlay() override;

	virtual void Tick(float _DeltaSecond) override;

private:

	UFUNCTION()
	void OnActorDestroy(AActor* _Destroy);

private:

	class AMyPlayerController* m_PlayerController = nullptr;

	FHitResult m_HitResult;

};
