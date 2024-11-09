// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IStoryWorldAccessor.h"
#include "StoryLineGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STORYLINE_API AStoryLineGameMode : public AGameModeBase, public IStoryWorldAccessor
{
	GENERATED_BODY()

public:
    // Sets default values for this actor's properties
	AStoryLineGameMode();

public:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "StoryLine|Test", DisplayName = "Add Story Line")
	void Test_AddStoryLine();

	UFUNCTION(BlueprintCallable, Category = "StoryLine|Test", DisplayName = "Initialize Story Line")
	void Test_InitializeStoryLine();
};
