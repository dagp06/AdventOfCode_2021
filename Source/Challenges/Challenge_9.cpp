#include "Challenge_9.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_9::sm_inputFilePath = "Inputs/Input_Challenge_9.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_9::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_rowSize = (int)lines[0].size();
    m_heightMap.resize(lines.size(), vector<int>(m_rowSize));
    for (int i = 0; i < lines.size(); ++i)
    {
        vector<int>& row = m_heightMap[i];
        const string& line = lines[i];
        for (int j = 0; j < line.size(); ++j)
        {
            row[j] = line[j] - '0';
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_9::Run_FirstPart()
{
    int riskLevel = 0;
    int lowPointCounts = 0;

    for (int rowIdx = 0; rowIdx < m_heightMap.size(); ++rowIdx)
    {
        for (int colIdx = 0; colIdx < m_rowSize; ++colIdx)
        {
            bool isLowest = true;
            int currentHeight = m_heightMap[rowIdx][colIdx];
            for (int yOffset = -1; yOffset <= 1; ++yOffset)
            {
                int y = rowIdx + yOffset;
                if (y < 0 || y >= m_heightMap.size())
                    continue;

                for (int xOffset = -1; xOffset <= 1; ++xOffset)
                {
                    int x = colIdx + xOffset;
                    if (x < 0 || x >= m_rowSize || xOffset == yOffset || (xOffset != 0 && yOffset != 0))
                        continue;

                    if (m_heightMap[y][x] <= currentHeight)
                    {
                        isLowest = false;
                        break;
                    }
                }

                if (!isLowest)
                {
                    break;
                }
            }

            if (isLowest)
            {
                riskLevel += currentHeight + 1;
                ++lowPointCounts;
            }
        }
    }

    if (!BENCHMARK)
        cout << "Done ! There are " << lowPointCounts << " low points. The total risk level is " << riskLevel << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_9::CleanUp_FirstPart()
{
    m_rowSize = 0;
    m_heightMap.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_9::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_rowSize = (int)lines[0].size();
    
    m_visited.resize(lines.size(), vector<bool>(m_rowSize, false));

    m_heightMap.resize(lines.size(), vector<int>(m_rowSize));
    for (int i = 0; i < lines.size(); ++i)
    {
        vector<int>& row = m_heightMap[i];
        const string& line = lines[i];
        for (int j = 0; j < line.size(); ++j)
        {
            row[j] = line[j] - '0';
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_9::Run_SecondPart()
{
    for (int rowIdx = 0; rowIdx < m_heightMap.size(); ++rowIdx)
    {
        for (int colIdx = 0; colIdx < m_rowSize; ++colIdx)
        {
            int basinSize = 0;
            ComputeBasinSize(rowIdx, colIdx, basinSize);

            if (basinSize > 0)
                m_basinSizes.insert(basinSize);
        }
    }

    int largestBasinsProduct = 1;
    int largestBasinsCount = 3;
    int i = 0;
    for (multiset<int>::const_reverse_iterator it = m_basinSizes.rbegin(); it != m_basinSizes.rend(); ++it)
    {
        largestBasinsProduct *= (*it);

        if (++i == largestBasinsCount)
            break;
    }

    if (!BENCHMARK)
        cout << "Done ! By multiplying together the sizes of the three largest basins, we get " << largestBasinsProduct << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_9::CleanUp_SecondPart()
{
    m_rowSize = 0;
    m_heightMap.clear();
    m_visited.clear();
    m_basinSizes.clear();
    return EErrorCode::Success;
}

void CChallenge_9::ComputeBasinSize(int _row, int _col, int& _basinSize)
{
    if (m_visited[_row][_col])
        return;

    m_visited[_row][_col] = true;
    if (m_heightMap[_row][_col] == 9)
        return;

    ++_basinSize;

    for (int yOffset = -1; yOffset <= 1; ++yOffset)
    {
        int y = _row + yOffset;
        if (y < 0 || y >= m_heightMap.size())
            continue;

        for (int xOffset = -1; xOffset <= 1; ++xOffset)
        {
            int x = _col + xOffset;
            if (x < 0 || x >= m_rowSize || xOffset == yOffset || (xOffset != 0 && yOffset != 0))
                continue;

            ComputeBasinSize(y, x, _basinSize);
        }
    }

}

