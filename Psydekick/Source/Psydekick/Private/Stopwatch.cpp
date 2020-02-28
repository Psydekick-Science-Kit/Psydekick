// Fill out your copyright notice in the Description page of Project Settings.


#include "Stopwatch.h"
#include "Misc/DateTime.h" 

void UStopwatch::Start()
{
    if(State != EStopwatchState::PAUSED)
    {
        AccumulatedTime = FTimespan::Zero();
    }
    
    State = EStopwatchState::RUNNING;
    LapStartTime = FDateTime::Now();
}

FTimespan UStopwatch::NewLap()
{
    FDateTime Now = FDateTime::Now();

    switch(State)
    {
        case EStopwatchState::RUNNING:
        case EStopwatchState::PAUSED:
            Laps.Add(GetCurrentTimeSince(Now));
            LapStartTime = Now;
            AccumulatedTime = FTimespan::Zero();
            State = EStopwatchState::RUNNING;

            return Laps.Last();
        default:
            Start();
            return FTimespan::Zero();
    }
}

FTimespan UStopwatch::PauseLap()
{
    switch(State)
    {
        case EStopwatchState::RUNNING:
            AccumulatedTime += FDateTime::Now() - LapStartTime;
            LapStartTime = FDateTime::MinValue();
            State = EStopwatchState::PAUSED;

            break;

        default:
            UE_LOG(LogPsydekick, Error, TEXT("Paused called when stopwatch was not running"));
    }

    return AccumulatedTime;
}

FTimespan UStopwatch::StopLap()
{    
    switch(State)
    {
        case EStopwatchState::RUNNING:
        case EStopwatchState::PAUSED:
            Laps.Add(GetCurrentTime());
            LapStartTime = FDateTime::MinValue();
            AccumulatedTime = FTimespan::Zero();
            State = EStopwatchState::STOPPED;

            return Laps.Last();

        default:
            UE_LOG(LogPsydekick, Error, TEXT("Stop called when stopwatch was not started"));
            return FTimespan::Zero();
    }

}

void UStopwatch::Reset()
{
    Laps.Empty();
    LapStartTime = FDateTime::MinValue();
    AccumulatedTime = FTimespan::Zero();
    State = EStopwatchState::STOPPED;
}

FTimespan UStopwatch::GetCurrentTime()
{
    return GetCurrentTimeSince(FDateTime::Now());
}

FTimespan UStopwatch::GetCurrentTimeSince(FDateTime When)
{
    switch(State)
    {
        case EStopwatchState::RUNNING:
            return AccumulatedTime + (When - LapStartTime);
        case EStopwatchState::PAUSED:
            return AccumulatedTime;
        default:
            return FTimespan::Zero();
    }
}
