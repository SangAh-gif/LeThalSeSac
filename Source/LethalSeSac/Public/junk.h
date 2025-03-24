// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "junk.generated.h"

/**
 * 
 */
UCLASS()
class LETHALSESAC_API Ajunk : public AItemBase
{
	GENERATED_BODY()


public:
	Ajunk();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
