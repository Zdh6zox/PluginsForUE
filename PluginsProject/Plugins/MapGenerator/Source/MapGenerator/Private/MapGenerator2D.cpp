// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator2D.h"
#include "Debug/MapGenerationDebugger.h"
#include "Division/Map2DRegionDivider_VD.h"
#include "Division/MapGeneratorRegionDivider.h"
#include "Division/MapDivisionParameters.h"
#include "Sampler/Map2DSampler_PoissonDisk.h"

FMapGenerator2D::FMapGenerator2D(const FMapGenerator2DSetting& generationSetting)
    : m_GenerationSetting(generationSetting)
{
    //currently use PossionDisk Sampler and VoronoiDiagram Division 
    m_MainNodeSampler = new FMap2DSampler_PoissonDisk();
    m_RegionNodeSampler = new FMap2DSampler_PoissonDisk();
    m_RegionDivider = new FMap2DRegionDivider_VD();
}

FMapGenerator2D::~FMapGenerator2D()
{
    delete m_MainNodeSampler;
    delete m_RegionNodeSampler;
    delete m_RegionDivider;
}

void FMapGenerator2D::AttachDebugger(FMapGenerationDebugger* debugger)
{
    m_Debugger = debugger;
    m_MainNodeSampler->AttachDebugger(m_Debugger);
    m_RegionNodeSampler->AttachDebugger(m_Debugger);
    m_RegionDivider->AttachDebugger(m_Debugger);
}

void FMapGenerator2D::Construct2DMap(FMap2DGenerationResult& generationResult)
{
    FMap2DBorder border(m_GenerationSetting.Map2DSizeLength, m_GenerationSetting.Map2DSizeWidth);
    FMap2DSampleSettings sampleSetting(m_GenerationSetting);

    TArray<FMap2DSite> generatedSites;
    TArray<FMap2DRegion> generatedRegions;

    //First, use sampler to generate main nodes
    m_Debugger->StartLogPeriod("[SampleIn2DMap]");
    m_MainNodeSampler->SampleIn2DMap(sampleSetting, generatedSites);
    m_Debugger->EndLogPeriod();

    //Second, use main nodes to generate regions
    TArray<FVector2D> regionOrigins;
    for (const FMap2DSite& site : generatedSites)
    {
        regionOrigins.Add(site.GetSiteLocation());
    }
    FMap2DDivisionParameters vdParameters(EMap2DDivisionMethodType::VoronoiDiagram, border, regionOrigins, m_GenerationSetting.VDRelaxationCycles);
    m_Debugger->StartLogPeriod("[Divide2DMap]");
    m_RegionDivider->Divide2DMap(vdParameters, generatedRegions);
    m_Debugger->EndLogPeriod();

    //Third, generate sub-nodes inside regions
    int regionInx = 0;
    for (FMap2DRegion& region : generatedRegions)
    {
        TArray<FVector2D> regionNodes;
        m_Debugger->StartLogPeriod(FString::Printf(TEXT("[SampleInRegion%d]"), regionInx));
        m_RegionNodeSampler->SampleInRegion(sampleSetting, region, generatedSites);
        m_Debugger->EndLogPeriod();
        regionInx++;
    }

    generationResult.GeneratedRegions = generatedRegions;
    generationResult.GeneratedSites = generatedSites;
}