// Fill out your copyright notice in the Description page of Project Settings.


#include "UAVGameModeBase.h"

AUAVGameModeBase::AUAVGameModeBase()
{
	//set the default pawn class to our custom pawn class
	DefaultPawnClass = AUAVPawn::StaticClass();
}