#pragma once

#include "Common/Challenge.h"
#include <list>
#include <queue>
using namespace std;

class CChallenge_6 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void Simulate(int _days);
    long long ComputeTotalLanternfish() const;

    int GetIndexForDay(const int& _index, const int& _day) const;

    static string const sm_inputFilePath;

    static const int ms_cycleDuration = 7;
    static const int ms_firstCycleDuration = 9;

    vector<long long> m_lanternfishCountPerTimerValue;
};
