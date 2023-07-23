// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Move.h"
#include "AICon_NormalMonster.h"
#include "../Character/NormalMonster.h"


UBTTask_NormalMonster_Move::UBTTask_NormalMonster_Move()
{

}
 

EBTNodeResult::Type UBTTask_NormalMonster_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::MOVE);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) TargetActor == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	int a = 0;

	{
		FVector TargetPos = TargetActor->GetActorLocation();
		FVector ThisPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
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

	
	{
		FVector PawnPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		FVector TargetPos = TargetActor->GetActorLocation();

		FVector Dir = TargetPos - PawnPos;

		GetNormalMonster(OwnerComp)->AddMovementInput(Dir);

		float AttackRagne = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRagne"));

		if (Dir.Size() <= AttackRagne)
		{
			SetStateChange(OwnerComp, NormalMonsterState::ATTACK);
			return;
		}
	}
}
