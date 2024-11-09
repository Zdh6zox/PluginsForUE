// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryLineBasic.h"
#include "StoryLineModule.h"
#include "StoryLinePlot.h"

StoryLineBasic::StoryLineBasic()
{
}

StoryLineBasic::~StoryLineBasic()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryLineBasic destructor called"));
    //Reset all plots
    for (auto iter = m_Plots.begin(); iter != m_Plots.end(); ++iter)
    {
        iter->reset();
    }
    m_Plots.clear();
}

void StoryLineBasic::Test_Initialize()
{
    std::shared_ptr<StoryLinePlot> uniquePtrPlot1(new StoryLinePlot());
    //std::shared_ptr<StoryLinePlot> uniquePtrPlot2(new StoryLinePlot());
    //std::shared_ptr<StoryLinePlot> uniquePtrPlot3(new StoryLinePlot());
    uniquePtrPlot1->Test_Initialize("Plot1");
    //uniquePtrPlot2->Test_Initialize();
    //uniquePtrPlot3->Test_Initialize();

    m_Plots.push_back(std::move(uniquePtrPlot1));
    //m_Plots.push_back(std::move(uniquePtrPlot2));
    //m_Plots.push_back(std::move(uniquePtrPlot3));
}
