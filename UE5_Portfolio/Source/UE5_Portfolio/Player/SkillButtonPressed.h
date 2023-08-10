// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillButtonPressed.generated.h"

UCLASS()
class UE5_PORTFOLIO_API ASkillButtonPressed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillButtonPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class APortfolioPlayerController* PlayerController = nullptr;

	FHitResult PlayerHitResult;
	bool bHitSuccessful = false;
};
