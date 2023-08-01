// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_RETURN.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../AI/AICon_NormalMonster.h"

UBTTask_Monster_RETURN::UBTTask_Monster_RETURN()
{

}

EBTNodeResult::Type UBTTask_Monster_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::RETURN);

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetNormalMonster(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 1000.0f;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Monster_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

#pragma region RETURN_DIRECTION_ROTATE
	
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

#pragma endregion

#pragma region RETURN_MOVE_TO_SPAWN_POS

	{
		FVector CurrentMonsterPos = GetNormalMonster(OwnerComp)->GetActorLocation();
		CurrentMonsterPos.Z = 0.0f;

		FVector MonsterSpawnPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
		MonsterSpawnPos.Z = 0.0f;

		FVector Dir = (MonsterSpawnPos - CurrentMonsterPos).GetSafeNormal();

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetNormalMonster(OwnerComp)->Controller, Dir);
		
		float Distance = (MonsterSpawnPos - CurrentMonsterPos).Size();


		if (Distance <= 10.0f)
		{
			int a = 0;
			SetNormalMonsterState(OwnerComp, NormalMonsterState::IDLE);
		}
	}


#pragma endregion

}
