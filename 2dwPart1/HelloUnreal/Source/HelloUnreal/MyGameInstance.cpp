// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));
	
	// 문자열 TEXT는 TCHAR 배열로 저장할 수 있다.
	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	// FString 객체를 이용한 문자열 출력
	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR* LongCharPtr = *LogCharString;
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	// FString.Contains 문자열 포함 검사 함수 ESearchCase 옵션을 지정 가능함(IgnoreCase = 대소문자 구별 안함, CaseSensitve = 대소문자 구별함)  
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		// Find 함수로 문자열 위치 찾기 -> Index 리턴
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		// Mid = 인자 인덱스부터 End까지 substring
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("FIND TEXT: %s"), *EndString);
	}

	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		// 그냥 빌드, 컴파일 할 시에 콘솔창에서 한글이 깨져서 출력된다.
		// 비주얼 스튜디어 파일 저장(save as)에서 인코딩을 UTF-8로 바꾸어서 저장하면 한글이 정상적으로 출력된다.
		UE_LOG(LogTemp,Log,TEXT("Split TEXT: %s 와 %s"), *Left, *Right);
	}

	int32 IntValue = 32;
	float FloatValue = 3.141592;

	FString FloatIntString = FString::Printf(TEXT("Int:%d Float:%f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int:%s Float:%s"), *IntString, *FloatString);

	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	FString FloatIntString2 = FString::Printf(TEXT("Int:%d Float:%f"), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString2);

	FName key1(TEXT("PELVIS"));
	FName key2(TEXT("pelvis"));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), key1 == key2 ? TEXT("같음") : TEXT("다름"));
	// 비교 결과는 같음이 출력된다. (FName은 대소문자를 구별하지 않는다.)

	// 빈번하게 호출되는 루프에서 
	for (int i = 0; i < 1000; ++i) 
	{
		// 생성자에 문자열을 넣으면 문자열 FName은 문자열을 Key로 변환한 다음에 그 key가 전역 pool에 있는지 조사하는 작업을 한다.
		// 오버헤드가 발생할 수 있기 때문에 자주 호출되는 함수에서는(ex)tic) FName을 선언해서 사용하는 것을 지양하자.
		FName SearchInNamePool = FName(TEXT("pelvis"));

		// 위의 방법으로 하지 않고 가급적이면 그 전에 한번 선언해주거나
		// 아래의 방법처럼 const로 한번만 처리하도록 해주는게 좋다
		// 초기화할 때 데이터를 저장하고 local static으로 선언했기 때문에 이 자체를 사용하면 된다.
		const static FName StaticOnlyOnce(TEXT("pelvis"));
	}
}
