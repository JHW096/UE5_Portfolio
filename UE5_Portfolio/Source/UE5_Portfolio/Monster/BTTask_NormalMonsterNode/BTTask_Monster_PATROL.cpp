// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Monster_PATROL.h"
#include "../../Global/TopDownGameInstance.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UBTTask_Monster_PATROL::UBTTask_Monster_PATROL()
{

}

EBTNodeResult::Type UBTTask_Monster_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	SetNormalMonsterState(OwnerComp, NormalMonsterState::IDLE);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;
	FVector OriginPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
	if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, 500.0f, RandomLocation))
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}

//void UBTTask_Monster_PATROL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//
//
//
//
//
//
//
//
//	/*UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//
//	FVector OriginPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
//
//	FNavLocation RandomLocation;
//	
//	if (GetStateTime(OwnerComp) >= 3.0f)
//	{
//		if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, 500.0f, RandomLocation))
//		{
//			GetBlackboardComponent(OwnerComp)->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
//		}
//		GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::PATROL);
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetNormalMonster(OwnerComp)->GetController(), RandomLocation);
//	}
//	
//
//	if (GetStateTime(OwnerComp) >= 3.0f && GetNormalMonster(OwnerComp)->GetVelocity().Size() <= 1.0f)
//	{
//		SetNormalMonsterState(OwnerComp, NormalMonsterState::IDLE);
//	}*/
//	
//
//
//
//
//	//SetNormalMonsterState(OwnerComp, NormalMonsterState::IDLE);
//
//
//
//	/*if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, 500.0f, RandomLocation))
//	{
//		GetBlackboardComponent(OwnerComp)->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
//	}
//
//	if (GetStateTime(OwnerComp) >= 1.0f)
//	{
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetNormalMonster(OwnerComp)->GetController(), RandomLocation);
//		FVector MonsterZeroZ = GetNormalMonster(OwnerComp)->GetActorLocation();
//		MonsterZeroZ.Z = 0.0f;
//		FVector RandomLocationZeroZ = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("PartolPos"));
//		RandomLocationZeroZ.Z = 0.0f;
//		float Dir = (MonsterZeroZ - RandomLocationZeroZ).Size();
//		int a = 0;
//		if (Dir <= 20.0f)
//		{
//			GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::IDLE);
//		}
//		else
//		{
//			GetNormalMonster(OwnerComp)->SetAnimState(NormalMonsterState::PATROL);
//		}
//		ResetStateTime(OwnerComp);
//	}*/
//	
//
//}
