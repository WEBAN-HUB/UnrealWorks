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


	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;
	// 1부터 10까지
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix);
	}

	// 짝수 부분 제거
	// 조건에 해당하는 구문을 보통 람다함수로 넣는다.
	Int32Array.RemoveAll(
		[](int32 val)
		{
			return val % 2 == 0;
		}
	);

	// +오퍼레이터 사용해서 데이터 추가하기
	// 디버그 모드로 변수 값을 확인하고 싶으면 브레이크 포인트를 걸고
	// 위의 옵션에서 Development Editor가 아닌 DebugGame Editor로 바꿔서 빌드하고 디버깅 해야한다.
	Int32Array += {2, 4, 6, 8, 10};

	TArray<int32> Int32ArrayCompare;
	// c 스타일의 원시 배열
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	// 초기화 되지 않은 데이터
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	// 원시 배열의 값을 Int32ArrayCompare에 복사해서 넣는다. 인자 1. 넣을 대상 2. 복사할 대상. 3. 사이즈
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);
	// ensure 구문을 통해 조건식이 맞지 않으면 로그에서 빨간색으로 에러가 표시된다.
	// 여기에서는 값이 같기 때문에 에러가 표시 되지 않음
	ensure(Int32Array == Int32ArrayCompare);

	// 기본적인 for문 활용 배열 순회
	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	ensure(Sum == 55);

	// 배열 총합을 얻을수 있는 Algo 라이브러리의 Accumulate함수 인자 1.합칠 자료구조 2. 초기값
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);

}
