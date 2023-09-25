// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"

UMyAnimNotifyState::UMyAnimNotifyState()
{
	MoveDistancePerSec = 0;
	TotalTime = 0;
}

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Owner = MeshComp->GetOwner();
	StartLocation = Owner->GetActorLocation();
	TotalDistance = TotalDuration * MoveDistancePerSec;

	TotalTime = TotalDuration;

	if (Owner != nullptr)
	{
		Owner->GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
		Owner->GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, FTimerDelegate::CreateLambda([this]()->void
		{
			if (Owner != nullptr)
			{
				FVector TargetLocation = StartLocation + Owner->GetActorForwardVector() * TotalDistance;
				Owner->SetActorLocation(TargetLocation);
			}
		}
		), TotalDuration, false
		);
	}

}

void UMyAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (Owner != nullptr)
	{
		if (Owner->GetWorld()->GetTimerManager().IsTimerActive(MoveTimerHandle))
		{
			float ElapsedTime = Owner->GetWorld()->GetTimerManager().GetTimerElapsed(MoveTimerHandle);
			float Ratio = ElapsedTime / TotalTime;

			FVector TargetLocation = StartLocation + Owner->GetActorForwardVector() * Ratio * TotalDistance;

			Owner->SetActorLocation(TargetLocation);
		}
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	Owner->SetActorLocation(Owner->GetActorLocation());
}
