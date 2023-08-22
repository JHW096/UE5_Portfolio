// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Bullet.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayer_Bullet::APlayer_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("PlayerAtt"), true);
	SphereComponent->ComponentTags.Add(FName("Bullet"));
	
	DestroyDistance = 2000.0f;
}

// Called when the game starts or when spawned
void APlayer_Bullet::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Bullet::BeginOverlap);

}

// Called every frame
void APlayer_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * 1500.0f);
	
	TArray<AActor*> arr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Player"), arr);
	FVector PlayerPos = arr[0]->GetActorLocation();
	
	float Distance = (PlayerPos - this->GetActorLocation()).Size();


	if (Distance > DestroyDistance)
	{
		this->Destroy();
	}
}

void APlayer_Bullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionProfileName() == TEXT("Monster"))
	{
		this->Destroy();
	}
}
