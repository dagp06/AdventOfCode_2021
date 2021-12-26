#pragma once

#include "Common/Challenge.h"

#include <list>
#include <map>

using namespace std;

class CChallenge_14 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    unsigned long long RunPairInsertionProcess(int _stepCount);

    static string const sm_inputFilePath;

    typedef pair<char, char> ElemPair;
    map<char, unsigned long long> m_polymerElemCount;
    map<ElemPair, unsigned long long> m_polymerPairCounts;
    map<ElemPair, vector<ElemPair>> m_pairInsertionRules;
};
