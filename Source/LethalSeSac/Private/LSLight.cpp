// Fill out your copyright notice in the Description page of Project Settings.


#include "LSLight.h"
#include "Components/SpotLightComponent.h"

ALSLight::ALSLight()
{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComp"));
	LightComp->SetupAttachment(MeshComp);

	curVal = 5;
}

void ALSLight::BeginPlay()
{
	Super::BeginPlay();
	LightComp->SetVisibility(false);
	
}

void ALSLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALSLight::UseItem()
{
	LightComp->SetVisibility(!LightComp->IsVisible());
	//if (LightComp->IsVisible())
	//{
	//	LightComp->SetVisibility(false);
	//}
	//else
	//{
	//	LightComp->SetVisibility(true);
	//}
}

