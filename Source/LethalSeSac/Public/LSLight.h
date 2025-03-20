// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "LSLight.generated.h"

/**
 * 
 */
UCLASS()
class LETHALSESAC_API ALSLight : public AItemBase
{
	GENERATED_BODY()
	
public:
	ALSLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* LightComp;



	virtual void UseItem() override;
};
