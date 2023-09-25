// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonster.h"
#include "../../Global/TopDownGameInstance.h"
#include "../Data/MonsterData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Global/TopDownGameInstance.h"
#include "Components/WidgetComponent.h"
#include "../Component/MonsterStatComponent.h"
#include "../Component/MonsterWidget.h"

AMeleeMonster::AMeleeMonster()
{
	//Monster Stat, UI
	{
		m_StatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("STATCOMPONENT"));

		m_HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_BAR"));
		m_HpBar->SetupAttachment(GetMesh());
		m_HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

		m_HpBar->SetWidgetSpace(EWidgetSpace::Screen);

		static ConstructorHelpers::FClassFinder<UUserWidget> MonsterHpBar
		(
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/MonsterUI/WBP_MonsterHP.WBP_MonsterHP_C'")
		);
		
		if (MonsterHpBar.Succeeded())
		{
			m_HpBar->SetWidgetClass(MonsterHpBar.Class);
			m_HpBar->SetDrawSize(FVector2D(200.0f, 50.0f));
		}
	}
	
}

void AMeleeMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_HpBar->InitWidget();

	auto HpWidget = Cast<UMonsterWidget>(m_HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(m_StatComponent);
	}

}

void AMeleeMonster::BeginPlay()
{
	UTopDownGameInstance* GameInstance = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInstance != nullptr)
	{
		NormalMonsterData = GameInstance->GetNormalMonsterData(MeleeMonsterName);

		for (TPair<NormalMonsterState, UAnimMontage*> pair : NormalMonsterData->NormalMonsterAnims)
		{
			PushAnimation(pair.Key, pair.Value);
		}
		SetAnimState(NormalMonsterState::IDLE);
	}

	Super::BeginPlay();

	FVector SpawnPos = GetActorLocation();

#pragma region SetBlackBoard

	GetBlackboardComp()->SetValueAsEnum(TEXT("NormalMonsterState"), static_cast<uint8>(NormalMonsterState::IDLE));
	GetBlackboardComp()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComp()->SetValueAsFloat(TEXT("SearchRange"), NormalMonsterData->SearchRange);
	GetBlackboardComp()->SetValueAsFloat(TEXT("AttackRange"), NormalMonsterData->AttackRange);
	GetBlackboardComp()->SetValueAsVector(TEXT("SpawnPos"), SpawnPos);
	GetBlackboardComp()->SetValueAsFloat(TEXT("RangeOver"), NormalMonsterData->RangeOver);

#pragma endregion 

#pragma region Delegate

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonster::BeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMeleeMonster::OnHit);
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonster::BeginOverlap);
	GetMesh()->OnComponentHit.AddDynamic(this, &AMeleeMonster::OnHit);

#pragma endregion



}

void AMeleeMonster::Tick(float DeltaSeconds)
{
	if (m_StatComponent->GetMonsterCurrentHp() <= 0)
	{
		this->Destroy();
	}
}

void AMeleeMonster::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag(TEXT("SnipeShoot")))
	{
		this->Destroy();
	}
}
void AMeleeMonster::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("FirstSkill")))
	{
		//OtherActor->Destroy();
	}
}

void AMeleeMonster::Destroyed()
{
	Super::Destroyed();

	UTopDownGameInstance* GameInstance = GetWorld()->GetGameInstance<UTopDownGameInstance>();

	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s(%u)GameInstacne == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	TSubclassOf<UObject> Item = GameInstance->GetSubClass(TEXT("Item"));

	for (size_t i = 0; i < 3; i++)
	{
		FVector RandomPos;

		RandomPos.X = UTopDownGameInstance::MainRandom.FRandRange(-50, 50);
		RandomPos.Y = UTopDownGameInstance::MainRandom.FRandRange(-50, 50);
		{
			AActor* Drop = GetWorld()->SpawnActor<AActor>(Item);
			Drop->ActorHasTag(TEXT("Item"));
			Drop->SetActorLocation(GetActorLocation() + RandomPos);
		}
	}

}

