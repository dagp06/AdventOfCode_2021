#pragma once

#include "Common/Challenge.h"

#include <set>

using namespace std;


class CChallenge_9 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void ComputeBasinSize(int _row, int _col, int& _basinSize);

    static string const sm_inputFilePath;

    int m_rowSize = 0;
    vector<vector<int>> m_heightMap;
    vector<vector<bool>> m_visited;
    multiset<int> m_basinSizes;
};
