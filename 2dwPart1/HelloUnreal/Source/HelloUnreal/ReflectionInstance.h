// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReflectionInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UReflectionInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UReflectionInstance();

	virtual void Init() override;
private:
	UPROPERTY()
	FString SchoolName;
};
