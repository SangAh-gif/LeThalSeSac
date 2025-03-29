// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCoilHeadFSM.h"
#include "LSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LSCoilHeadAnim.h"
#include "LSCoilHead.h"
#include "NavigationSystem.h"
#include "LSCoilHeadController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values for this component's properties
ULSCoilHeadFSM::ULSCoilHeadFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSCoilHeadFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALSCharacter::StaticClass());
	
	target = Cast<ALSCharacter>(actor);

	me = Cast<ALSCoilHead>(GetOwner());

	Anim = Cast <ULSCoilHeadAnim>(me->GetMesh()->GetAnimInstance());

	ai = Cast<ALSCoilHeadController>(me->GetController());
}


// Called every frame
void ULSCoilHeadFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, logMsg);

	switch (mState)
	{
	case ECoilHeadState::Idle:     { IdleState();     } break;
	case ECoilHeadState::Patrol:   { PatrolState();   } break;
	case ECoilHeadState::Attack:   { AttackState();   } break;
	case ECoilHeadState::Move:     { MoveState();     } break;
	case ECoilHeadState::LookAtMe: { LookAtMeState(); } break;
		default:
			break;
	}
}

void ULSCoilHeadFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= IdleDelayTime)
	{
		mState          = ECoilHeadState::Patrol;
		currentTime     = 0.0f;
		Anim->AnimState = mState;
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500.0f, randomPos);
	}
}	

void ULSCoilHeadFSM::MoveState()
{
}

void ULSCoilHeadFSM::PatrolState()
{
	me->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	auto result = ai->MoveToLocation(randomPos);
	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		GetRandomPositionInNavMesh(me->GetActorLocation(), 1000.0f, randomPos);
	}
		
}

void ULSCoilHeadFSM::AttackState()
{

}

void ULSCoilHeadFSM::LookAtMeState()
{

}

bool ULSCoilHeadFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);

	dest = loc.Location;

	return result;
}

