// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryLineCircumstance.h"

#include "StoryLineCondition.h"
#include "StoryLineModule.h"
#include "StoryLinePlot.h"

StoryLineCircumstance::StoryLineCircumstance()
{
}

StoryLineCircumstance::~StoryLineCircumstance()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryLineCircumstance destructor called"));
    m_Condition.reset();
    m_NextPlot.reset();
}

void StoryLineCircumstance::Test_Initialize(std::weak_ptr<StoryLinePlot>&& ownerPlot)
{
    std::shared_ptr<StoryLineCondition> uniquePtrCondition(new StoryLineCondition());
    m_Condition = std::move(uniquePtrCondition);

    m_OwnerPlot = std::move(ownerPlot);
    m_NextPlot = std::move(ownerPlot);
}
