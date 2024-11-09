// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/MapGenerationDebugString.h"
#include "MapGenerator.h"

void FMapGenerationDebugString::DebugDisplay(UWorld* world) const
{
    UE_LOG(LogMapGenerator, Log, TEXT("%s"), *m_Str);
}