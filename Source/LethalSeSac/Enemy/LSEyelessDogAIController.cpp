// Fill out your copyright notice in the Description page of Project Settings.


#include "LSEyelessDogAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "perception/AISenseConfig_Damage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LSEyelessDog.h"
#include "LSDogFSM.h"
#include "Perception/AIPerceptionTypes.h"


ALSEyelessDogAIController::ALSEyelessDogAIController()
{

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	DamageConfig->SetMaxAge(3.0f);
	PerceptionComp->ConfigureSense(*DamageConfig);

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HaaringConfig"));
	HearingConfig->SetMaxAge(3.0f);

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 600.0f; // 감지 거리 조절 
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

		PerceptionComp->ConfigureSense(*HearingConfig);
		PerceptionComp->SetDominantSense(HearingConfig->GetSenseImplementation());
	}

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ALSEyelessDogAIController::PerceptionUpdated);
}


void ALSEyelessDogAIController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//if(!PerceptionComp) return;

	//for (AActor* UpdatedActor : UpdatedActors)
	//{
	//	if (!UpdatedActor->ActorHasTag("enemy"))
	//	{
	//		FVector NoiseLocation = FVector::ZeroVector; // 감지된 위치 저장

	//		if(CanSenseActor(UpdatedActor, enemyAISenseEyelessDog::Damage) || CanSenseActor(UpdatedActor, enemyAISenseEyelessDog::Hearing))
	//		{
	//			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("hello"));

	//			ALSEyelessDog* enemy = Cast<ALSEyelessDog>(GetCharacter());
	//			if (enemy)
	//			{
	//				enemy->FindComponentByClass<ULSDogFSM>()->mState = EEnemyState::Move;
	//			}
	//			if (!NoiseLocation.IsZero())
	//			{
	//				MoveToLocation(NoiseLocation);
	//			}
	//		}
	//	}
	//}

	for (AActor* UpdatedActor : UpdatedActors)
	{
		if (!UpdatedActor->ActorHasTag("enemy"))
		{
			FActorPerceptionBlueprintInfo Info;
			PerceptionComp->GetActorsPerception(UpdatedActor, Info);
			FVector NoiseLocation = FVector::ZeroVector;

			for (const FAIStimulus& Stimulus : Info.LastSensedStimuli)
			{
				if (UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) == UAISense_Hearing::StaticClass())
				{
					NoiseLocation = Stimulus.StimulusLocation;
					ALSEyelessDog* enemy = Cast<ALSEyelessDog>(GetCharacter());
					if (enemy)
					{
						enemy->FindComponentByClass<ULSDogFSM>()->mState = EEnemyState::Move;
						MoveToLocation(NoiseLocation);
						UE_LOG(LogTemp, Log, TEXT("Moving to noise at %s"), *NoiseLocation.ToString());
					}
					break;
				}
			}
		}
	}
}

bool ALSEyelessDogAIController::CanSenseActor(AActor* actor, enemyAISenseEyelessDog AIPerceptionSense)
{
	FActorPerceptionBlueprintInfo ActorPerceptionBlueprintInfo;
	FAIStimulus ResultStimulus;

	PerceptionComp->GetActorsPerception(actor, ActorPerceptionBlueprintInfo);
	TSubclassOf<UAISense> QuerySenseClass;

	switch (AIPerceptionSense)
	{
	case enemyAISenseEyelessDog::Damage:
		QuerySenseClass = UAISense_Damage::StaticClass();
		break;
	case enemyAISenseEyelessDog::Hearing:
		QuerySenseClass = UAISense_Hearing::StaticClass();
		break;
	default:
		break;
	}

	TSubclassOf<UAISense> LastSensedStimulusClass;

	for (const FAIStimulus& AIStimulus : ActorPerceptionBlueprintInfo.LastSensedStimuli)
	{
		LastSensedStimulusClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulus);

		if (QuerySenseClass == LastSensedStimulusClass)
		{
			return true;
		}
	}
	return false;
}

