#include "StoryLineGameMode.h"

//Test
#include "StoryLineBasic.h"
#include "StoryWorld.h"
#include "StoryLineModule.h"

AStoryLineGameMode::AStoryLineGameMode()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void AStoryLineGameMode::BeginPlay()
{
    Super::BeginPlay();

    OnGameStart();
}

void AStoryLineGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    OnGameEnd();
}

void AStoryLineGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    Update();
}

void AStoryLineGameMode::Test_AddStoryLine()
{
    UE_LOG(LogStoryLine, Log, TEXT("Test Add Story Line"));
    StoryLineBasic* newLine = new StoryLineBasic();
    g_StoryWorld->AddStoryLine(std::move(*newLine));
}

void AStoryLineGameMode::Test_InitializeStoryLine()
{
    UE_LOG(LogStoryLine, Log, TEXT("Test Initialize Story Line"));
    std::shared_ptr<StoryLineBasic> newLine(new StoryLineBasic());
    newLine->Test_Initialize();
    g_StoryWorld->AddStoryLine(std::move(newLine));
}