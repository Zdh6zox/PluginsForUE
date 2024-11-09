// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryWorld.h"

#include "StoryLineBasic.h"
#include "StoryLineModule.h"

StoryWorld* StoryWorld::ms_Instance = new StoryWorld();

StoryWorld::StoryWorld()
{
}

StoryWorld::~StoryWorld()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryWorld destructor called"));
    ClearStoryLines();
}

StoryWorld* StoryWorld::GetInstance()
{
    return ms_Instance;
}

void StoryWorld::OnGameStart()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryWorld OnGameStart"));
}

void StoryWorld::OnGameEnd()
{
    UE_LOG(LogStoryLine, Log, TEXT("StoryWorld OnGameEnd"));
    ClearStoryLines();
}

void StoryWorld::Update()
{
    //UE_LOG(LogStoryLine, Log, TEXT("StoryWorld Update"));
}

bool StoryWorld::AddStoryLine(StoryLineBasic&& newLine)
{
    m_StoryLines.push_back(std::move(std::unique_ptr<StoryLineBasic>(&newLine)));

    UE_LOG(LogStoryLine, Log, TEXT("StoryLines Size: %d"), m_StoryLines.size());
    return true;
}

bool StoryWorld::AddStoryLine(std::shared_ptr<StoryLineBasic>&& newLine)
{
    m_StoryLines.push_back(std::move(newLine));

    UE_LOG(LogStoryLine, Log, TEXT("StoryLines Size: %d"), m_StoryLines.size());
    return true;
}

void StoryWorld::ClearStoryLines()
{
    auto iter = m_StoryLines.begin();
    for (; iter != m_StoryLines.end(); ++iter)
    {
        iter->reset();
    }

    m_StoryLines.clear();
}