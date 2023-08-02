// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Monster_MOVE.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../AI/AICon_NormalMonster.h"

UMyBTTask_Monster_MOVE::UMyBTTask_Monster_MOVE()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMyBTTask_Monster_MOVE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::MOVE);

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetNormalMonster(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 250.0f;
	}

	return EBTNodeResult::InProgress;
}

void UMyBTTask_Monster_MOVE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) TargetActor == nullptr"), __FUNCTION__, __LINE__);
		SetNormalMonsterState(OwnerComp, NormalMonsterState::RETURN);
		return;
	}

#pragma region OnwerDirection
	{
		FVector TargetPos = TargetActor->GetActorLocation();
		TargetPos.Z = 0.0f;

		FVector OwnerPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		OwnerPos.Z = 0.0f;

		FVector Dir = TargetPos - OwnerPos;
		Dir.Normalize();

		FVector OtherForward = GetNormalMonster(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DeltaSeconds });
			GetNormalMonster(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else
		{
			FRotator Rot = Dir.Rotation();
			GetNormalMonster(OwnerComp)->SetActorRotation(Rot);
		}
	}
#pragma endregion

#pragma region OwnerMoveToTarget, SetAttack
	{
		//OwnerMoveToTarget
		AActor* DestActor = Cast<AActor>(GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor")));
		FVector Dest = DestActor->GetActorLocation();
		FVector Start = GetNormalMonster(OwnerComp)->GetActorLocation();

		FVector Dir = Dest - Start;

		if (DestActor != nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(GetNormalMonster(OwnerComp)->Controller, DestActor);
		}


		//SetAttack
		float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
		float AttackRagne = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));


		if (SearchRange < Dir.Size())
		{
			// 원재 라리로 돌아가고
			SetNormalMonsterState(OwnerComp, NormalMonsterState::RETURN);
			return;
		}
		if (Dir.Size() <= AttackRagne)
		{
			SetNormalMonsterState(OwnerComp, NormalMonsterState::ATTACK);
			return;
		}

	}
#pragma endregion


#pragma region RANGEOVER_
	{
		FVector CurrentMonsterPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		CurrentMonsterPos.Z = 0.0f;

		FVector MonsterSpawnPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
		MonsterSpawnPos.Z = 0.0f;

		float OverRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("RangeOver"));

		float Distance = (MonsterSpawnPos - CurrentMonsterPos).Size();

		if (Distance >= OverRange)
		{
			int a = 0;
			SetNormalMonsterState(OwnerComp, NormalMonsterState::RETURN);
		}
	}

	

#pragma endregion

}
