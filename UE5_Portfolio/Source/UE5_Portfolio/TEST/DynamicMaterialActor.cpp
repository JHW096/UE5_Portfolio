// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicMaterialActor.h"
#include "../Portfolio/MainPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADynamicMaterialActor::ADynamicMaterialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADynamicMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DynamicMaterialMesh"));
	DynamicMaterialMesh->CreateDynamicMaterialInstance(0);

}

// Called every frame
void ADynamicMaterialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AMainPlayer* P = Cast<AMainPlayer>(Player);

	TArray<FHitResult> OutHits;
	FVector Start = P->GetActorLocation() - FVector(0.0f, 0.0f, P->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()); // Line start
	FVector End = P->GetActorLocation() + FVector(-500.0f, 0.0f, 500.0f);
	FName ProfileName = TEXT("CoverToPlayer");
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);

	if (OutHits.Num() != 0)
	{
		//DynamicMaterialMesh->SetVectorParameterValueOnMaterials()
	}
		 

}

