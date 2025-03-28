// Fill out your copyright notice in the Description page of Project Settings.


#include "LSGameModeBase.h"
#include "ValueSaveGame.h"
#include "Kismet/GameplayStatics.h"

void ALSGameModeBase::BeginPlay()
{
	LoadGameData();
	if (bInSpace) 
	{
		if (GameDay <= 0)
		{
			ResetGameData();
		}
	}
	LoadGameData();
}

void ALSGameModeBase::SaveGameData()
{
	UValueSaveGame* sg = Cast<UValueSaveGame>(UGameplayStatics::CreateSaveGameObject(UValueSaveGame::StaticClass()));

	sg->TotValueSave = TotValue;
	sg->bInSpace = bInSpace;
	sg->CurGameDay = GameDay;

	UGameplayStatics::SaveGameToSlot(sg, SaveSlotName, UserIndex);
}

void ALSGameModeBase::LoadGameData()
{
	bool sgExist = UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex);

	if(!sgExist) return;

	UValueSaveGame* sg = Cast<UValueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

	if(!sg) return;

	TotValue = sg->TotValueSave;
	bInSpace = sg->bInSpace;
	GameDay = sg->CurGameDay;
}

void ALSGameModeBase::ResetGameData()
{
	bool sgExist = UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex);

	if (!sgExist) return;

	UValueSaveGame* sg = Cast<UValueSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

	if (!sg) return;

	sg->TotValueSave = sg->DefaultTotValueSave;
	sg->bInSpace = sg->DefaultbInSpace;
	sg->CurGameDay = sg->DefaultCurGameDay;

	SaveGameData();
}