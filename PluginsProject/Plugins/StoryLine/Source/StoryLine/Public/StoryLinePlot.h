// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryLineIncludes.h"

/**
 * 
 */
class StoryLineCircumstance;
class StoryLineCircumstancePicker;
class STORYLINE_API StoryLinePlot
{
public:
	StoryLinePlot();
	~StoryLinePlot();

	//Test for construct and destruct
	void Test_Initialize(FString plotName);

private:
	std::vector<std::shared_ptr<StoryLineCircumstance>> m_PossibleCircumstances;
	std::shared_ptr<StoryLineCircumstancePicker> m_CircumstancePicker;
	FString m_PlotName;
};
