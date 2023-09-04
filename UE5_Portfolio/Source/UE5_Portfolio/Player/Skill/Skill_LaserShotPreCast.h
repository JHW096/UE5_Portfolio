// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_LaserShotPreCast.generated.h"

UCLASS()
class UE5_PORTFOLIO_API ASkill_LaserShotPreCast : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_LaserShotPreCast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnActorDestroy(AActor* _Destroy);

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SubClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_NextActor;
};
