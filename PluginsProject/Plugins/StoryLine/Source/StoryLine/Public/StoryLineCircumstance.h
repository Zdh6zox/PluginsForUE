// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryLineIncludes.h"

/**
 * 
 */
class StoryLinePlot;
class StoryLineCondition;
class STORYLINE_API StoryLineCircumstance
{
public:
	StoryLineCircumstance();
	~StoryLineCircumstance();

	// Test for construct and destruct
	void Test_Initialize(std::weak_ptr<StoryLinePlot>&& ownerPlot);

protected:
	std::shared_ptr<StoryLineCondition> m_Condition;
	std::weak_ptr<StoryLinePlot> m_OwnerPlot;
	std::weak_ptr<StoryLinePlot> m_NextPlot;
};
