// Fill out your copyright notice in the Description page of Project Settings.


#include "IStoryWorldAccessor.h"

#include "StoryWorld.h"

void IStoryWorldAccessor::OnGameStart()
{
    g_StoryWorld->OnGameStart();
}

void IStoryWorldAccessor::OnGameEnd()
{
    g_StoryWorld->OnGameEnd();
}

void IStoryWorldAccessor::Update()
{
    g_StoryWorld->Update();
}