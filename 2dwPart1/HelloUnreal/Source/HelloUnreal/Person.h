// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();

	UFUNCTION()
	virtual void DoLesson();

	// 함수 뒤에 붙은 const는 함수가 속해있는 클래스의 멤버 변수를 바꾸지 않겠다는 의미
	// 함수 앞에 붙은 const는 함수의 리턴값을 상수화 시키겠다는 의미
	const FString& GetName() const;
	void SetName(const FString& InName);

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:

};
