// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillTileViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UPlayerSkillTileViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:


private:

	void SetTableRowName();
	FName GetTableRowName(int _Key);
	class UPlayerSkillWidget* CreateSkillWidget(FName _Name);

private:

	UPROPERTY(Category = "InvenList", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTileView* InvenList = nullptr;

	TArray<UUserWidget> m_SkillWidgetList;

	TMap<int, FName> TableRowNameMap;
};
