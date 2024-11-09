// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/MapGenerationDebugger.h"
#include "Debug/MapGenerationDebugElement.h"
#include "Debug/MapGenerationDebugString.h"
#include "Debug/MapGenerationDebugSphere.h"
#include "MapGeneratorTestActor.h"

FMapGenerationDebugger::~FMapGenerationDebugger()
{
    ClearDebugLogs();
}

void FMapGenerationDebugger::SetDebugOwner(AMapGeneratorTestActor* owner)
{
    m_Owner = owner;
}

void FMapGenerationDebugger::AddDebugLog(IMapGenerationDebugElement* debugElement)
{
    m_DebugElementsMap.FindOrAdd(m_CurPeriodInx).Add(debugElement);
    m_DebugElements.Add(debugElement);
}

void FMapGenerationDebugger::ClearDebugLogs()
{
    m_DebugElementsMap.Empty();
    for (IMapGenerationDebugElement* element :m_DebugElements)
    {
        delete element;
    }

    m_DebugElements.Empty();
    m_PeriodNameMap.Empty();
}

void FMapGenerationDebugger::StartLogPeriod(FString periodName)
{
    m_PeriodNameMap.FindOrAdd(m_CurPeriodInx, periodName);
}

void FMapGenerationDebugger::EndLogPeriod()
{
    m_CurPeriodInx++;
}

int FMapGenerationDebugger::GetPeriodSize() const
{
    TArray<int> keys;
    m_DebugElementsMap.GetKeys(keys);
    return keys.Num();
}

int FMapGenerationDebugger::GetPeriodElementSize(int periodInx) const
{
    const TArray<IMapGenerationDebugElement*>* periodElements = m_DebugElementsMap.Find(periodInx);
    return periodElements->Num();
}

void FMapGenerationDebugger::DebugDisplayElement(UWorld* world, int periodInx, int elementInx) const
{
    const TArray<IMapGenerationDebugElement*>* periodElements = m_DebugElementsMap.Find(periodInx);
    periodElements->GetData()[elementInx]->DebugDisplay(world);
}

void FMapGenerationDebugger::AddDebugString(FString debugStr)
{
    FMapGenerationDebugString* strElement = new FMapGenerationDebugString(debugStr);
    AddDebugLog(strElement);
}

void FMapGenerationDebugger::AddDebugSphere(FVector2D sphereLoc, FColor sphereColor)
{
    FVector Loc3D = FVector(sphereLoc.X, sphereLoc.Y, 0.0f);
    FMapGenerationDebugSphere* sphereElement = new FMapGenerationDebugSphere(m_Owner->GetActorLocation() + Loc3D, m_Owner->SiteDisplayRadius, sphereColor);
    AddDebugLog(sphereElement);
}