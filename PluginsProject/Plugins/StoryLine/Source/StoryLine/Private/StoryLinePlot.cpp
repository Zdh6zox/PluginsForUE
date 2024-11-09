// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryLinePlot.h"

#include "StoryLineCircumstance.h"
#include "StoryLineModule.h"
#include "StoryLineCircumstancePicker.h"

StoryLinePlot::StoryLinePlot()
{
}

StoryLinePlot::~StoryLinePlot()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryLinePlot %s destructor called"), *m_PlotName);
    //Reset all circumstances
    for (auto iter = m_PossibleCircumstances.begin(); iter != m_PossibleCircumstances.end(); ++iter)
    {
        iter->reset();
    }
    m_PossibleCircumstances.clear();

    m_CircumstancePicker.reset();
}

void StoryLinePlot::Test_Initialize(FString plotName)
{
    std::shared_ptr<StoryLineCircumstancePicker> uniquePtrPicker(new StoryLineCircumstancePicker());
    m_CircumstancePicker = std::move(uniquePtrPicker);

    std::shared_ptr<StoryLineCircumstance> uniquePtrCircumstance1(new StoryLineCircumstance());
    std::shared_ptr<StoryLineCircumstance> uniquePtrCircumstance2(new StoryLineCircumstance());
    uniquePtrCircumstance1->Test_Initialize(std::move(std::make_shared<StoryLinePlot>(*this)));
    uniquePtrCircumstance2->Test_Initialize(std::move(std::make_shared<StoryLinePlot>(*this)));

    m_PossibleCircumstances.push_back(std::move(uniquePtrCircumstance1));
    m_PossibleCircumstances.push_back(std::move(uniquePtrCircumstance2));

    m_PlotName = plotName;
}
