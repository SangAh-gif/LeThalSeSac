// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class LETHALSESAC_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	virtual void UseItem();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 minVal= 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 maxVal = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 curVal = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UImage* Img;


};
