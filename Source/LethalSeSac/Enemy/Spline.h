// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.generated.h"

UCLASS()
class LETHALSESAC_API ASpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USplineComponent* splinecomp;

	void IncrementPatrolRoute();
	FVector GetSplinePointasWorldPosition();

	int32 PatrollIndex;
	int32 Direction;
	FVector splinelocation;

};
