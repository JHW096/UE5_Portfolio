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

	class UTileView* m_SkillTileView = nullptr;

private:

	const int32 PLAYERSKILLNUM = 4;

	TArray<FName> PlayerSkillName;

};
