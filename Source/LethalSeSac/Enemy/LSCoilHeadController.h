// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LSCoilHeadController.generated.h"

/**
 * 
 */

 UENUM()
	 enum class enemyAISenseCoilHead
 {
	Damage,
	Sight
 };

UCLASS()
class LETHALSESAC_API ALSCoilHeadController : public AAIController
{
	GENERATED_BODY()

public:
	ALSCoilHeadController();

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* PerceptionComp; // ���� �ý��� 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAISense_Damage* DamageConfig;

	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	bool CanSenseActor(AActor* actor, enemyAISenseCoilHead AIPerceptionSense);

	bool isDead = false;

	void OnPlayerLookedAtAI();

	class LSCoilHeadFSM* coilHeadFSM;
	
};
