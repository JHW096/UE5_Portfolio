// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchRangeOver.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../../Monster/Character/NormalMonster.h"
#include "../../Monster/AI/AICon_NormalMonster.h"

UBTService_SearchRangeOver::UBTService_SearchRangeOver()
{

}

void UBTService_SearchRangeOver::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
	float RangeOver = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("RangeOver"));

	FVector SpawnPos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("SpawnPos"));
	FVector MonsterPos = GetNormalMonster(OwnerComp)->GetActorLocation();
	FVector PlayerPos;
	float Dir;
	float Dir2 = (SpawnPos - MonsterPos).Size();

	AActor* FindTarget = GetTargetSearch(OwnerComp);

	if (FindTarget != nullptr)
	{
		PlayerPos = FindTarget->GetActorLocation();
		Dir = (PlayerPos - MonsterPos).Size();
	}

	if (Dir > RangeOver || Dir > SearchRange)
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("IsReturn"), true);
	}
	else
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsBool(TEXT("IsReturn"), false);
	}
	
	
	
}

ANormalMonster* UBTService_SearchRangeOver::GetNormalMonster(UBehaviorTreeComponent& OwnerComp)
{
	AAICon_NormalMonster* AI_Controller = GetBlackboardComponent(OwnerComp)->GetOwner<AAICon_NormalMonster>();
	if (AI_Controller == nullptr || AI_Controller->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterAIController is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ANormalMonster* NormalMonsterPawn = AI_Controller->GetPawn<ANormalMonster>();
	if (NormalMonsterPawn == nullptr || NormalMonsterPawn->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : MonsterPawn is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return NormalMonsterPawn;
}

UBlackboardComponent* UBTService_SearchRangeOver::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("%s(%u) : BlackBoard is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	return Blackboard;
}

AActor* UBTService_SearchRangeOver::GetTargetSearch(UBehaviorTreeComponent& OwnerComp)
{
	AActor* FindTarget = nullptr;

	FString TargetTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	ANormalMonster* OwnerActor = GetNormalMonster(OwnerComp);

	float SearchRagne = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

	if (TargetActors.Num() != 0)
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Distance = (OwnerActor->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRagne <= Distance)
			{
				continue;
			}

			if (Range > Distance)
			{
				Range = Distance;
				FindTarget = TargetActors[i];
			}
		}
	}

	return FindTarget;
}
