// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STORYLINE_API UTestBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "StoryLine|Test", DisplayName = "AddStoryLine")
	static void Test_AddStoryLine();

    UFUNCTION(BlueprintCallable, Category = "StoryLine|Test", DisplayName = "ClearStoryLine")
    static void Test_ClearStoryLine();
};
