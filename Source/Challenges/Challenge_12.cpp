#include "Challenge_12.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_12::sm_inputFilePath = "Inputs/Input_Challenge_12.txt";
CChallenge_12::Cave const CChallenge_12::sm_startCave = "start";
CChallenge_12::Cave const CChallenge_12::sm_endCave = "end";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (const string& line : lines)
    {
        vector<string> lineSplit;
        FileHelper::SplitLine(line, "-", lineSplit);

        // Add connections between caves
        m_cavesConnections[lineSplit[0]].push_back(lineSplit[1]);
        m_cavesConnections[lineSplit[1]].push_back(lineSplit[0]);
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::Run_FirstPart()
{
    int pathCount = 0;
    CountPaths(sm_startCave, pathCount, false);

#if !defined(BENCHMARK)
    cout << "Done ! There are " << pathCount << " paths.";
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_FirstPart()
{
    m_cavesConnections.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (const string& line : lines)
    {
        vector<string> lineSplit;
        FileHelper::SplitLine(line, "-", lineSplit);

        // Add connections between caves
        m_cavesConnections[lineSplit[0]].push_back(lineSplit[1]);
        m_cavesConnections[lineSplit[1]].push_back(lineSplit[0]);
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::Run_SecondPart()
{
    int pathCount = 0;
    CountPaths(sm_startCave, pathCount, true);

#if !defined(BENCHMARK)
    cout << "Done ! There are " << pathCount << " paths.";
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_SecondPart()
{
    m_cavesConnections.clear();
    return EErrorCode::Success;
}

void CChallenge_12::CountPaths(const Cave& _currentCave, int& _pathCount, bool _canVisitASmallCaveTwice, set<Cave> _visitedCaves /*= set<Cave>()*/)
{
    if (_currentCave == sm_endCave)
    {
        ++_pathCount;
        return;
    }

    if (IsASmallCave(_currentCave))
    {
        // If cave was visited already
        if (_visitedCaves.find(_currentCave) != _visitedCaves.end())
        {
            // Cannot revisit this cave.
            if (!_canVisitASmallCaveTwice || _currentCave == sm_startCave || _currentCave == sm_endCave)
            {
                return;
            }

            // Increment visits count
            _canVisitASmallCaveTwice = false;
        }
        else
        {
            // Store visited cave
            _visitedCaves.insert(_currentCave);
        }
    }

    for (const Cave& connection : m_cavesConnections.at(_currentCave))
    {
        CountPaths(connection, _pathCount, _canVisitASmallCaveTwice, _visitedCaves);
    }
}