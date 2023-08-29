// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "NiagaraComponent.h"
#include "ProjectileShoot.generated.h"

UCLASS()
class UE5_PORTFOLIO_API AProjectileShoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(Category = "Component", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent = nullptr;


private:
	//Relative Projectile Path 
	FVector m_StartPos;
	FVector m_DestPos;
	float m_arcValue = 0.5f;
	FVector m_OutVelocity = FVector(50, 0, 200);

	FPredictProjectilePathParams m_ProjectilePathParams;
	FPredictProjectilePathResult m_ProjectilePathResult;
};
