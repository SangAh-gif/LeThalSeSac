// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ValueSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LETHALSESAC_API UValueSaveGame : public ULocalPlayerSaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	bool bInSpace;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 CurGameDay;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 TotValueSave;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 QuotaSave;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	bool DefaultbInSpace = true;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 DefaultCurGameDay = 1;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 DefaultTotValueSave = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Default|SaveGame")
	int32 DefaultQuotaSave = 200;
};
