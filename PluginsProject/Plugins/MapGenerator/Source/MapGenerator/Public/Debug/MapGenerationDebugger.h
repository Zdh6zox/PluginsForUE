// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class IMapGenerationDebugElement;
class AMapGeneratorTestActor;
class MAPGENERATOR_API FMapGenerationDebugger
{
public:
    FMapGenerationDebugger() {}
    ~FMapGenerationDebugger();

    void AddDebugString(FString debugStr);
    void AddDebugSphere(FVector2D sphereLoc, FColor sphereColor);
    void StartLogPeriod(FString periodName);
    void EndLogPeriod();
    void ClearDebugLogs();
    int GetPeriodSize() const;
    int GetPeriodElementSize(int periodInx) const;
    void DebugDisplayElement(UWorld* world, int periodInx, int elementInx) const;
    void SetDebugOwner(AMapGeneratorTestActor* owner);

private:
    void AddDebugLog(IMapGenerationDebugElement* debugElement);
    TMap<int, TArray<IMapGenerationDebugElement*>> m_DebugElementsMap;
    TMap<int, FString> m_PeriodNameMap;
    TArray<IMapGenerationDebugElement*> m_DebugElements;
    int m_CurPeriodInx{ 0 };
    AMapGeneratorTestActor* m_Owner{ nullptr };
};
