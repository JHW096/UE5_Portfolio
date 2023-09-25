// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillTileViewWidget.h"
#include "PlayerSkillWidget.h"
#include "../../Player/Data/PlayerSkillData.h"
#include "../../Global/TopDownGameInstance.h"
#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "../../Portfolio/PortfolioHUD.h"
#include "../../Player/Character/PlayerCharacter.h"

void UPlayerSkillTileViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//PlayerSkillName = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetSkillName();
	

}

void UPlayerSkillTileViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

