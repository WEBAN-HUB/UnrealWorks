// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_INTERFACE_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName){ Name = InName; }

	FORCEINLINE const class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }
protected:
	UPROPERTY()
	FString Name;
	// 전방 선언 (헤더를 참조하지 않아도 단순히 포인터 크기만큼의 메모리를 잡으면서도 의존성을 최대한 없앨 수 있다.)
	// UE4까지 권장되던 방식
	//UPROPERTY()
	//class UCard* Card;
	TObjectPtr<class UCard> Card;
};
