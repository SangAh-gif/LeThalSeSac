// Fill out your copyright notice in the Description page of Project Settings.


#include "LSCoilHeadController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ALSCoilHeadController::ALSCoilHeadController()
{
    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

    SetPerceptionComponent(*PerceptionComp);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius     = 500.0f;
    SightConfig->LoseSightRadius = 800.0f;
    SightConfig->PeripheralVisionAngleDegrees = 50.0f; 
    SightConfig->SetMaxAge(3.0f);

}

void ALSCoilHeadController::BeginPlay()
{
    Super::BeginPlay();
}

void ALSCoilHeadController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}

bool ALSCoilHeadController::CanSenseActor(AActor* actor, enemyAISenseCoilHead AIPerceptionSense)
{
    return false;
}

void ALSCoilHeadController::OnPlayerLookedAtAI()
{
}
