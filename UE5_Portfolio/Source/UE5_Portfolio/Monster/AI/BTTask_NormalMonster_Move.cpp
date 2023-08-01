// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalMonster_Move.h"
#include "AICon_NormalMonster.h"
#include "../Character/NormalMonster.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalMonster_Move::UBTTask_NormalMonster_Move()
{

}
 

EBTNodeResult::Type UBTTask_NormalMonster_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::MOVE);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	


	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NormalMonster_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (TargetActor == nullptr)
	{
		SetStateChange(OwnerComp, NormalMonsterState::RETURN);
		UE_LOG(LogTemp, Log, TEXT("%s(%u) TargetActor == nullptr"), __FUNCTION__, __LINE__);
		return;
	}


	//Rotate
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

	
//#pragma region NormalMove
//	//Chagne Attack
//	{
//		FVector PawnPos = GetNormalMonster(OwnerComp)->GetActorLocation();
//		FVector TargetPos = TargetActor->GetActorLocation();
//
//		FVector Dir = TargetPos - PawnPos;
//
//		GetNormalMonster(OwnerComp)->AddMovementInput(Dir);
//
//		float AttackRagne = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));
//
//		if (Dir.Size() <= AttackRagne)
//		{
//			SetStateChange(OwnerComp, NormalMonsterState::ATTACK);
//			return;
//		}
//	}
//#pragma endregion

	//Navsystem Move

#pragma region MyMove
	{
		AActor* DestActor = Cast<AActor>(GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor")));
		FVector Dest = DestActor->GetActorLocation();
		FVector Start = GetNormalMonster(OwnerComp)->GetActorLocation();

		FVector Dir = (Dest - Start);
		if (DestActor != nullptr)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetNormalMonster(OwnerComp)->Controller, Dest);

			//GetNormalMonster(OwnerComp)->AddMovementInput(Dir, 1.0f, false);
		}

		
		float AttackRagne = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));

		if (Dir.Size() <= AttackRagne)
		{
			SetStateChange(OwnerComp, NormalMonsterState::ATTACK);
			return;
		}


	}
#pragma endregion


	//
	{
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

		if (Blackboard == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("%s, %u : Blackboard == nullptr"), __FUNCTION__, __LINE__);
			return; 
		}

		FString TargetTag = Blackboard->GetValueAsString(TEXT("TargetTag"));
		TArray<AActor*> TargetActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

		ANormalMonster* ThisMonster = GetNormalMonster(OwnerComp);
		float SearchRagne = Blackboard->GetValueAsFloat(TEXT("SearchRange"));

		if (TargetActors.Num() != 0)
		{
			AActor* Target = nullptr;
			float Range = TNumericLimits<float>::Max();

			for (size_t i = 0; i < TargetActors.Num(); i++)
			{
				float Distance = (ThisMonster->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

				if (SearchRagne <= Distance)
				{
					continue;
				}

				if (Range > Distance)
				{
					Range = Distance;
					Target = TargetActors[i];
				}
			}
			if (Target == nullptr)
			{
				int a = 0;
				SetStateChange(OwnerComp, NormalMonsterState::RETURN);
			}

		}
	}
	//{

	//	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	//	if (Blackboard == nullptr)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("%s, %u : Blackboard is nullptr"), __FUNCTION__, __LINE__);
	//		return;
	//	}

	//	FString TargetTag = Blackboard->GetValueAsString(TEXT("TargetTag"));
	//	TArray<AActor*> TargetActors;
	//	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);


	//	ANormalMonster* ThisMonster = GetNormalMonster(OwnerComp);
	//	float SearchRagne = Blackboard->GetValueAsFloat(TEXT("SearchRange"));


	//	if (TargetActors.Num() != 0)
	//	{
	//		AActor* TargetAggro = nullptr;
	//		float Range = TNumericLimits<float>::Max();

	//		for (size_t i = 0; i < TargetActors.Num(); i++)
	//		{
	//			float Distance = (ThisMonster->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

	//			if (SearchRagne <= Distance)
	//			{
	//				continue;
	//			}

	//			//가장 가까운 거리의 Player Actor를 찾는 과정
	//			if (Range > Distance)
	//			{
	//				Range = Distance;
	//				TargetAggro = TargetActors[i];
	//			}
	//		}

	//		if (TargetAggro == nullptr)
	//		{
	//			int a = 0;
	//			SetStateChange(OwnerComp, NormalMonsterState::RETURN);
	//		}

	//		if (TargetAggro != nullptr)
	//		{
	//			GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), TargetAggro);
	//			SetStateChange(OwnerComp, NormalMonsterState::MOVE);
	//			return;
	//		}
	//	}
	//}
}
