// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillTileViewWidget.h"
#include "PlayerSkillWidget.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPlayerSkillTileViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UPlayerSkillTileViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


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
		return;
	}

	UPlayerSkillWidget* PlayerSkillWidget;
	PlayerSkillWidget->PlayerSkillWidgetSetting(PlayerSkillData);
}
