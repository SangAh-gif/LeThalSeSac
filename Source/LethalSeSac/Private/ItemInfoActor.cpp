// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoActor.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LSCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AItemInfoActor::AItemInfoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(sceneComp);

	ItemNameComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemNameComp"));
	ItemNameComp->SetupAttachment(RootComponent);
	ItemNameComp->SetRelativeLocation(FVector(0,5,30));
	ItemNameComp->SetRelativeRotation(FRotator(0, 180, 0));
	ItemNameComp->SetWorldSize(15);

	ItemValComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemValComp"));
	ItemValComp->SetupAttachment(RootComponent);
	ItemValComp->SetRelativeLocation(FVector(0, 7, 20));
	ItemValComp->SetRelativeRotation(FRotator(0, 180, 0));
	ItemValComp->SetWorldSize(10);

}

// Called when the game starts or when spawned
void AItemInfoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemInfoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ALSCharacter*  player= Cast<ALSCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if (player)
	{
		FVector Dir = GetActorLocation() - player->VRCamera->GetComponentLocation();
		SetActorRotation(Dir.Rotation());
	}
}

void AItemInfoActor::SetInfo(FString Name, int32 val)
{
	ItemNameComp->SetText(FText::FromString(Name));
	ItemValComp->SetText(FText::AsNumber(val));
	
}

