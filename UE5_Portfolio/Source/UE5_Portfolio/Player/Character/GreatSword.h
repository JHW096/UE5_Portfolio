// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GreatSword.generated.h"

UCLASS()
class UE5_PORTFOLIO_API AGreatSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGreatSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UFUNCTION()
		void OnCharacterOverlap(
			UPrimitiveComponent* Overlap,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

public:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* m_Weapon;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* m_Trigger;

};
