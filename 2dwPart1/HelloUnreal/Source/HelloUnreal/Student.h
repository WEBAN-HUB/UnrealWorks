// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h" // 다른 헤더파일을 include할 때 generated.h가 제일 아래에 선언되어야 한다.
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UStudent : public UPerson
{
	GENERATED_BODY()
public:
	UStudent();

	// 상속받은 DoLesson함수가 이미 UFUNCTION()매크로가 적용되어 있기 때문에 추가로 작성할 필요가 없다.
	virtual void DoLesson() override;

private:
	UPROPERTY()
	int32 Id;
};
