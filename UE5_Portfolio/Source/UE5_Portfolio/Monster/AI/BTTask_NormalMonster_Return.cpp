// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Return.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalMonster_Return::UBTTask_NormalMonster_Return()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_NormalMonster_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Animation -> Normal
	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::RETURN);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Return::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	int a = 0;

	//Monster Return Rotaiton
	{
		FVector CurrentMonsterPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		CurrentMonsterPos.Z = 0.0f;

		FVector MonsterSpawnPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
		MonsterSpawnPos.Z = 0.0f;
		
		FVector Dir = MonsterSpawnPos - CurrentMonsterPos;
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

	
	//Monster Return Movement
	{
		FVector CurrentMonsterPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		CurrentMonsterPos.Z = 0.0f;

		FVector MonsterSpawnPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
		MonsterSpawnPos.Z = 0.0f;

		FVector Dir = MonsterSpawnPos - CurrentMonsterPos;

		Dir.Normalize();

		GetNormalMonster(OwnerComp)->AddMovementInput(Dir * 1000.0f * DeltaSeconds);

		float Distance = (MonsterSpawnPos - CurrentMonsterPos).Size();


		if (Distance <= 10.0f)
		{
			SetStateChange(OwnerComp, NormalMonsterState::IDLE);
		}
	}
	

	

	
}
