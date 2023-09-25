// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimInstance.h"
#include "MyAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UMyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	UMyAnimNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	float MoveDistancePerSec;

private:

	FVector StartLocation;

	float TotalDistance;

	float TotalTime;

	AActor* Owner;

	FTimerHandle MoveTimerHandle;

};
