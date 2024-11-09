// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapGenerator2DSetting.h"
#include "Map2DBorder.h"
/**
 * 
 */
class FMap2DSampleSettings
{
public:
    FMap2DSampleSettings() {}
    FMap2DSampleSettings(const FMapGenerator2DSetting& settings)
    {
        m_MainNodeCount = settings.MainNodeCount;
        m_SubNodeCount = settings.SubNodeCount;
        m_MainNodeRadius = settings.MainNodeImpactRadius;
        m_SubNodeRadius = settings.SubNodeImpactRadius;
        m_MapSizeWidth = settings.Map2DSizeWidth;
        m_MapSizeLength = settings.Map2DSizeLength;
        m_IterationCandidateNum = settings.IterationCandidateNum;
    }

public:
    FMap2DBorder GetBorder() const { return FMap2DBorder(m_MapSizeLength, m_MapSizeWidth); }
    int m_IterationCandidateNum;
    int m_MainNodeCount;
    int m_SubNodeCount;
    float m_MainNodeRadius;
    float m_SubNodeRadius;
    float m_MapSizeWidth;
    float m_MapSizeLength;
};
