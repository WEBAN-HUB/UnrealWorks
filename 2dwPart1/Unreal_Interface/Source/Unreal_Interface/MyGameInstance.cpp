// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 인자에 this를 넣어주면서 MyGameInstance가 CourseInfo의 Outer가 되었고 CourseInfo는 Subobject가 되었다.
	CourseInfo = NewObject<UCourseInfo>(this);
	UE_LOG(LogTemp, Log, TEXT("=================================="));

	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	CourseInfo->OnChanged.AddUObject(Student1,&UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("=================================="));
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>()};

	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름 : %s"),*Person->GetName());
	}
	UE_LOG(LogTemp, Log, TEXT("=================================="));

	for (const auto Person : Persons)
	{
		// 형변환 방법
		// 형변환 실패시 Null을 받게 된다.
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("=================================="));

	for (const auto Person : Persons)
	{
		const UCard* OneCard = Person->GetCard();
		check(OneCard);
		ECardType CardType = OneCard->GetCardType();
		//UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %d"), *Person->GetName(), CardType);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/Unreal_Interface.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %s"), *Person->GetName(), *CardMetaData)
		}
	}
	UE_LOG(LogTemp, Log, TEXT("=================================="));
}
