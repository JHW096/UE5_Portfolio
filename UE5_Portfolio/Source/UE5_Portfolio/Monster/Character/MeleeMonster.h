// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AINormalMonster.h"
#include "../Data/NormalMonsterState.h"
#include "MeleeMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AMeleeMonster : public AAINormalMonster
{
	GENERATED_BODY()

	AMeleeMonster();

	virtual void PostInitializeComponents() override;

	void BeginPlay() override;
	
	const struct FMonsterData* NormalMonsterData;


private:

	UFUNCTION()
	void BeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit
	);

	void Destroyed() override;

private:

	UPROPERTY(Category = "MeleeInfo", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName MeleeMonsterName = "NONE";

	UPROPERTY(VisibleAnywhere)
	class UMonsterStatComponent* m_StatComponent;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* m_HpBar;
};
