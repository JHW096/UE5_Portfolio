// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "TopDownGameInstance.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	UTopDownGameInstance* GameInst = GetWorld()->GetGameInstance<UTopDownGameInstance>();
	m_ItemData = GameInst->GetItemData();
	
	if (m_ItemData->Mesh != nullptr)
	{
		UActorComponent* Component = GetComponentByClass(UStaticMeshComponent::StaticClass());
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);

		if (StaticMesh != nullptr)
		{
			StaticMesh->SetStaticMesh(m_ItemData->Mesh);
		}
	}

}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AItemBase::Take(AActor* _Actor)
{


}
