// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LSDogFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8 
{
	Idle,
	Move,
	Attack,
	Damage,
	Die
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LETHALSESAC_API ULSDogFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULSDogFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	void IdleState();

	void MoveState();

	void Attack();

	void DamageState();

	void DieState();


	UPROPERTY(VisibleAnywhere, Category = FSM)
	class ALSCharacter* target;

	UPROPERTY()
	class ALSEyelessDog* me;


	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float IdleDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float currentTime = 0.0f;

	// 길찾기 수행시 랜덤위치 
	FVector randomPos;

	// 랜덤 위치 가져오기
	//bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);

	//UPROPERTY()
	//class AAIController* ai;

};
