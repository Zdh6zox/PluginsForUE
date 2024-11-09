// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map2DBorder.h"
/**
 * 
 */
enum MAPGENERATOR_API EMap2DDivisionMethodType
{
    invalid,
    VoronoiDiagram
};

class MAPGENERATOR_API FMap2DDivisionParameters
{
public:
    FMap2DDivisionParameters(EMap2DDivisionMethodType methodType, const FMap2DBorder& mapBorder)
    {
        checkf(methodType != EMap2DDivisionMethodType::invalid, TEXT("illegal division parameter constructed"));
        m_MethodType = methodType;
        m_MapBorder = mapBorder;
    }
    FMap2DDivisionParameters(EMap2DDivisionMethodType methodType, const FMap2DBorder& mapBorder, const TArray<FVector2D>& regionOrigins, int relaxationCycles)
    {
        checkf(methodType == EMap2DDivisionMethodType::VoronoiDiagram, TEXT("illegal division parameter constructed"));
        m_MethodType = methodType;
        m_MapBorder = mapBorder;
        m_RegionOrigins = regionOrigins;
        m_RelaxationCycles = relaxationCycles;
    }

    //FMap2DDivisionParameters& operator=(const FMap2DDivisionParameters& rhs)
    //{
    //    m_MethodType = rhs.GetMethodType();
    //    m_MapBorder = rhs.GetMap2DBorder();
    //    m_RegionOrigins = rhs.GetRegionOrigins();
    //    m_RelaxationCycles = rhs.GetRelaxationCycles();
    //    return *this;
    //}

    EMap2DDivisionMethodType GetMethodType() const { return m_MethodType; }
    const FMap2DBorder& GetMap2DBorder() const { return m_MapBorder; }
    TArray<FVector2D> GetRegionOrigins() const { return m_RegionOrigins; }
    int GetRelaxationCycles() const { return m_RelaxationCycles; }

private:
    EMap2DDivisionMethodType m_MethodType;
    TArray<FVector2D> m_RegionOrigins;
    FMap2DBorder m_MapBorder;
    int m_RelaxationCycles;
};
