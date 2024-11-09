// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMapGenerationDebugElementType : uint8
{
    String,
    Sphere,
    Invalid
};

class UWorld;
class MAPGENERATOR_API IMapGenerationDebugElement
{
public:
    virtual ~IMapGenerationDebugElement(){}
    virtual void DebugDisplay(UWorld* world) const = 0;
};
