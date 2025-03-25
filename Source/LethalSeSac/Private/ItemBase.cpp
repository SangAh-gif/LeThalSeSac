// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("Item"));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("itemcheck"));
	BoxComp->SetSimulatePhysics(true);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionProfileName(TEXT("Item"));

	ItemInfoComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("ItemInfoComp"));
	ItemInfoComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<AActor> TempInfo(TEXT("/Script/Engine.Blueprint'/Game/KHH/Blueprints/BP_ItemInfo.BP_ItemInfo_C'"));
	if (TempInfo.Succeeded())
	{
		ItemInfoComp->SetChildActorClass(TempInfo.Class);
	}
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	ItemInfoComp->SetVisibility(false);
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowInfo)
	{
		curtime += DeltaTime;
		if (curtime >= ShowTime)
		{
			bShowInfo = false;
			ItemInfoComp->SetVisibility(false);
			curtime = 0;
		}
	}
}

void AItemBase::UseItem()
{

}

void AItemBase::ShowInfo()
{
	FString str = GetActorNameOrLabel();
	bShowInfo = true;
	ItemInfoComp->SetVisibility(true);
	UE_LOG(LogTemp,Warning,TEXT("%s"),*str);
}

