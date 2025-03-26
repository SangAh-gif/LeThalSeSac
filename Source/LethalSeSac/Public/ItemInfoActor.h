// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInfoActor.generated.h"

UCLASS()
class LETHALSESAC_API AItemInfoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemInfoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* sceneComp;
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* ItemNameComp;
	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* ItemValComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	void SetInfo(FString Name, int32 val);
};
