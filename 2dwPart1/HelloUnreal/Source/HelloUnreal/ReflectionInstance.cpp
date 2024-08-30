// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionInstance.h"

// 헤더파일의 리플렉션 정보를 변경하거나 생성자코드에서 Class Default Object(CDO)의 기본값을 변경하는 경우 에디터를 종료하고 켜야 변경점 확인 가능하다 
UReflectionInstance::UReflectionInstance()
{
	SchoolName = TEXT("기본학교");
}

void UReflectionInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("========================"));
	UClass* ClassRuntime = GetClass(); // 런타임 중에 UReflectionInstance클래스 정보 가져오기
	UClass* ClassCompile = UReflectionInstance::StaticClass(); // 컴파일 타임 중에 UReflectionInstance 정보 가져오기

	// check라고 하는 Assertion 함수 -> 반드시 검증하고 넘어가야 하는 상황에 사용 -> 같은지 판별하는 if 역할
	// check(ClassRuntime != ClassCompile); 결과가 false인 경우 Assertion fail 에러 발생 -> 에디터가 강제로 종료된다
	// 실제 게임으로 빌드하면 적용되지 않음 (에러 발생하지 않는다)
	check(ClassRuntime == ClassCompile);
	// ensure는 check와 같은 역할을 하지만 에디터는 종료되지 않고 로그에 에러 발생 메세지를 출력한다.
	// ensure(ClassRuntime != ClassCompile);
	// ensureMsgf는 메세지를 지정 가능
	// ensureMsgf(ClassRuntime != ClassCompile, TEXT("에러 발생시 출력할 메세지"));

	UE_LOG(LogTemp,Log,TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRuntime->GetName()); // 한글을 쓰고 있기 때문에 인코딩을 변경해야한다. 1.File 2. Save filename as 3. save 옆 Encoding 설정 UTF-8

	SchoolName = TEXT("변경한 학교");

	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UReflectionInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("========================"));
}
