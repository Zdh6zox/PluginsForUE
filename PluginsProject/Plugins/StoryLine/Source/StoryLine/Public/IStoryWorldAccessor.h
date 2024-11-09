// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STORYLINE_API IStoryWorldAccessor
{
protected:
    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void Update();
};
