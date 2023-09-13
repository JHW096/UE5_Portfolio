// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillTileViewWidget.h"
#include "PlayerSkillWidget.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"
#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"
#include "SkillWidgetObject.h"
#include "Components/ProgressBar.h"

void UPlayerSkillTileViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetTableRowName();

	m_SkillList = Cast<UTileView>(GetWidgetFromName(TEXT("PlayerSkillTileView")));

	if (m_SkillList == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerSkillTileView is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	m_SkillList->AddItem(CreateSkillWidgetObject(GetTableRowName(0)));

}

void UPlayerSkillTileViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	

}

void UPlayerSkillTileViewWidget::SetSkillWidgetProgressBarPercent(size_t _Value)
{
	//num - 1 = 0 > 0
	if (m_SkillWidgetList.Num() - 1 > _Value || _Value < 0 || _Value >= PLAYER_SKILL_SIZE)
	{
		return;
	}

	if (m_SkillWidgetList[_Value] == nullptr)
	{
		return;
	}
	UProgressBar* ProgressBar = m_SkillWidgetList[_Value]->GetProgressBar();

	float TempRatio = (float)m_SkillWidgetList[_Value]->GetMaxCoolTime() / (float)m_SkillWidgetList[_Value]->GetMaxCoolTime();
	ProgressBar->SetPercent(TempRatio);
}

UPlayerSkillWidget* UPlayerSkillTileViewWidget::GetPlayerSkillWidgetFromTileView(size_t _Value)
{
	if (m_SkillWidgetList.Num() - 1 > _Value || _Value < 0 || _Value >= PLAYER_SKILL_SIZE)
	{
		return nullptr;
	}

	if (m_SkillWidgetList[_Value] == nullptr)
	{
		return nullptr;
	}

	return m_SkillWidgetList[_Value];
}

void UPlayerSkillTileViewWidget::SetTableRowName()
{
	TableRowNameMap.Add(TTuple<int, FName>(0, FName("SnipeShot")));
	TableRowNameMap.Add(TTuple<int, FName>(1, FName("LaserShot")));
}

FName UPlayerSkillTileViewWidget::GetTableRowName(int _Key)
{
	return *TableRowNameMap.Find(_Key);
}

UPlayerSkillWidget* UPlayerSkillTileViewWidget::CreateSkillWidget(FName _Name)
{
	FPlayerSkillData* PlayerSkillData = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetPlayerSkillData(_Name);
	if (PlayerSkillData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerSkillData == nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}
	
	

	UPlayerSkillWidget* PlayerSkillWidget = NewObject<UPlayerSkillWidget>();
	PlayerSkillWidget->PlayerSkillWidgetSetting(PlayerSkillData);
	PlayerSkillWidget->SetProgressBar();

	int a = 0;

	return PlayerSkillWidget;
}

USkillWidgetObject* UPlayerSkillTileViewWidget::CreateSkillWidgetObject(FName _Name)
{
	USkillWidgetObject* SkillWidgetObject = NewObject<USkillWidgetObject>();

	UTopDownGameInstance* GameInstance = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) GameInstance is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	FPlayerSkillData* PlayerSkillData = GameInstance->GetPlayerSkillData(_Name);
	if (PlayerSkillData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%u) PlayerSkillData is nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	SkillWidgetObject->SetPlayerSkillWidget(CreateSkillWidget(_Name));
	SkillWidgetObject->SetPlayerSkillData(PlayerSkillData);

	int a = 0;

	m_SkillWidgetList.Add(SkillWidgetObject->GetPlayerSkillWidget());

	return SkillWidgetObject;
}
