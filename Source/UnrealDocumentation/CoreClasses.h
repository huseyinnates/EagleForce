// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 

class UNREALDOCUMENTATION_API CoreClasses : UObject
{
public:
	CoreClasses();
	~CoreClasses();

private:
	UFUNCTION(BlueprintCallable, Category = "CoreClasses")
	FString CoreClassesTest();
};
