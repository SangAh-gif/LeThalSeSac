// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "ItemInfoActor.h"

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
	ConstructorHelpers::FClassFinder<AItemInfoActor> TempInfo(TEXT("/Script/Engine.Blueprint'/Game/KHH/Blueprints/BP_ItemInfo.BP_ItemInfo_C'"));
	if (TempInfo.Succeeded())
	{
		ItemInfoComp->SetChildActorClass(TempInfo.Class);
	}
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	//ItemInfoComp->SetVisibility(false);
	ItemInfoComp->SetRelativeScale3D(FVector(1,1,0));
	AItemInfoActor* ItemInfo = Cast<AItemInfoActor>(ItemInfoComp->GetChildActor());
	if (ItemInfo)
	{
		ItemInfo->SetInfo(ItemName, curVal);
	}
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
			//ItemInfoComp->SetVisibility(false);
			GetWorld()->GetTimerManager().SetTimer(ShrinkTimer, FTimerDelegate::CreateLambda(
				[this]()
				{
					scale = FMath::Lerp(scale, 0, 20 * GetWorld()->DeltaTimeSeconds);
					ItemInfoComp->SetRelativeScale3D(FVector(scale));
					if (scale <= 0.05)
					{
						scale = 0;
						ItemInfoComp->SetRelativeScale3D(FVector(scale));
						GetWorldTimerManager().ClearTimer(ShrinkTimer);
					}
				}), 0.02f, true);
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
	GetWorld()->GetTimerManager().SetTimer(ShowTimer, FTimerDelegate::CreateLambda(
		[this]()
		{
			scale += 0.2f;
			ItemInfoComp->SetRelativeScale3D(FVector(scale));
			if (scale >= 1)
			{
				scale = 1;
				ItemInfoComp->SetRelativeScale3D(FVector(scale));
				GetWorldTimerManager().ClearTimer(ShowTimer);
			}
		}), 0.02f, true);
	
}

