// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("서지혁");
	//FNAME인 경우 NAME 접두사를 넣어주는 것이 일반적
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}
