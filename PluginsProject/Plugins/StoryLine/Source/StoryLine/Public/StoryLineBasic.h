// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryLineIncludes.h"
/**
 * 
 */
class StoryLinePlot;
class STORYLINE_API StoryLineBasic
{
public:
	StoryLineBasic();
	~StoryLineBasic();

	//Test for construct and destruct
	void Test_Initialize();

protected:
	std::vector<std::shared_ptr<StoryLinePlot>> m_Plots;
};
