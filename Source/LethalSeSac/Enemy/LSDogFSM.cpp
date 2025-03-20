// Fill out your copyright notice in the Description page of Project Settings.


#include "LSDogFSM.h"
#include "LSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LSEyelessDog.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "AITypes.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "NavigationSystem.h"

// Sets default values for this component's properties
ULSDogFSM::ULSDogFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSDogFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// 월드에서 Player 찾아오기 
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALSCharacter::StaticClass());

	target = Cast<ALSCharacter>(actor);

	// 소유 객체
	me = Cast<ALSEyelessDog>(GetOwner());

	//ai = Cast<AAIController>(me->GetController());
}


// Called every frame
void ULSDogFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	// 실행창에 상태 메세지 출력하기 
	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, logMsg);

	switch (mState)
	{
	case EEnemyState::Idle:
	{
		IdleState();
	}
		break;
	case EEnemyState::Move:
	{
		MoveState();
	}
		break;
	case EEnemyState::Attack:
	{
		Attack();
	}
		break;
	case EEnemyState::Damage:
	{
		DamageState();
	}
		break;
	case EEnemyState::Die:
	{
		DieState();
	}
		break;
	case EEnemyState::Patrol:
	{
		PatrolState();
	}
	break;
	default:
		break;
	}
}

void ULSDogFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > IdleDelayTime)
	{
		mState = EEnemyState::Move;

		currentTime = 0.0f;

		// Anim->AnimState = mState;
		
		//GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	}

}

void ULSDogFSM::MoveState()
{

	// 바로 나에게 오는 것 
	/*
	

	*/

	// 타겟 목적지가 필요하다.
	FVector desttination = target->GetActorLocation();

	// 방향
	FVector dir = desttination - me->GetActorLocation();

	me->AddMovementInput(dir);

	//auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// 목적지 길찾기 경로 데이터 검색
	FPathFindingQuery query;
	 
	FAIMoveRequest req; 
	

	/*if (!target || !me) return;
	FVector destination = target->GetActorLocation();
	FVector         dir = destination - me->GetActorLocation();

	FRotator newRotation = dir.Rotation();
	newRotation = UKismetMathLibrary::MakeRotFromXZ(dir, me->GetActorUpVector());
	newRotation = FMath::RInterpTo(me->GetActorRotation(), newRotation, GetWorld()->GetDeltaSeconds(), 1.5f);
	me->SetActorRotation(newRotation);

	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;
	FAIMoveRequest req;

	req.SetAcceptanceRadius(3);
	req.SetGoalLocation(destination);

	ai->BuildPathfindingQuery(req, query);
	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		me->GetCharacterMovement()->MaxWalkSpeed =600.0f;
		ai->MoveToLocation(destination);

	}
	else
	{
		auto result = ai->MoveToLocation(randomPos);

	}*/
	
	
	//FVector desttination
}

void ULSDogFSM::Attack()
{

}

void ULSDogFSM::DamageState()
{
}

void ULSDogFSM::DieState()
{
}

void ULSDogFSM::PatrolState()
{

}

bool ULSDogFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;

	return result; 
}

