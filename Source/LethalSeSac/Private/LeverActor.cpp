// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ALeverActor::ALeverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetRelativeLocation(FVector((-130.000000, 9010.000000, 1225.000000)));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/SSA/Ship/ShipMesh/Lever_001_Baked1.Lever_001_Baked1'"));
	if (TempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(TempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ALeverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

