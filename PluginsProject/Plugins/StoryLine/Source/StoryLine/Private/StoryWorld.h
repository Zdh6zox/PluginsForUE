// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryLineIncludes.h"
/**
 * 
 */
class StoryLineBasic;
class STORYLINE_API StoryWorld
{
public:
    static StoryWorld* GetInstance();
    void OnGameStart();
    void OnGameEnd();
	void Update();
	bool AddStoryLine(StoryLineBasic&& newLine);
	bool AddStoryLine(std::shared_ptr<StoryLineBasic>&& newLine);

private:
	StoryWorld();
	~StoryWorld();
	StoryWorld(const StoryWorld& other);
	const StoryWorld& operator=(const StoryWorld& other);

    void ClearStoryLines();

private:
	static StoryWorld* ms_Instance;
	std::vector<std::shared_ptr<StoryLineBasic>> m_StoryLines;
};

#define g_StoryWorld StoryWorld::GetInstance()
