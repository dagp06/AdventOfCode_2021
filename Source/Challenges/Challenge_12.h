#pragma once

#include "Common/Challenge.h"

#include <map>
#include <list>
#include <set>

using namespace std;

class CChallenge_12 : public CChallenge
{
private:
    typedef string Cave;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void CountPaths(const Cave& _currentCave, int& _pathCount, bool _canVisitASmallCaveTwice, set<Cave> _visitedCaves = set<Cave>());

    static bool IsASmallCave(const Cave& _cave) { return _cave.empty() ? false : _cave[0] > 'Z'; }

    static string const sm_inputFilePath;
    static Cave const sm_startCave;
    static Cave const sm_endCave;

    map<Cave, list<Cave>> m_cavesConnections;
};
