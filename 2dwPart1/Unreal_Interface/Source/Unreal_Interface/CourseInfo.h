// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

// 델리게이트 함수에는 보통 끝에 Signature를 붙인다
DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);

/**
 * 
 */
UCLASS()
class UNREAL_INTERFACE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
public:

	UCourseInfo();

	FCourseInfoOnChangedSignature OnChanged;

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	UPROPERTY()
	FString Contents;


};
