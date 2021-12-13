#pragma once

#include "Common/Challenge.h"

#include <set>

using namespace std;

class CChallenge_7 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    long long ComputeTotalFuelConsumed(int _pos, bool _constantCost) const;
    static long long ComputeFuelConsumed(int _distance, bool _constantCost);

    int m_lowMeanPos = 0;
    multiset<int> m_horizontalPosSet;
};
