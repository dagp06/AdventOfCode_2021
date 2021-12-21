#include "Challenge_11.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_11::sm_inputFilePath = "Inputs/Input_Challenge_11.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_rowSize = lines[0].size();
    m_energyLevelGrid.resize(lines.size(), Row<int>(m_rowSize));
    for (int row = 0; row < lines.size(); ++row)
    {
        for (int col = 0; col < m_rowSize; ++col)
        {
            m_energyLevelGrid[row][col] = lines[row][col] - '0';
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::Run_FirstPart()
{
    int stepCount = 100;
    int flashCount = 0;
    Simulate(stepCount, flashCount);

#if !defined(BENCHMARK)
    cout << "Done ! After simulating " << stepCount << " steps, the has been a total of " << flashCount << " flashes." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_FirstPart()
{
    m_rowSize = 0;
    m_energyLevelGrid.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_rowSize = lines[0].size();
    m_energyLevelGrid.resize(lines.size(), Row<int>(m_rowSize));
    for (int row = 0; row < lines.size(); ++row)
    {
        for (int col = 0; col < m_rowSize; ++col)
        {
            m_energyLevelGrid[row][col] = lines[row][col] - '0';
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::Run_SecondPart()
{
    int stepCount = 0;
    FindFirstSynchronizedFlashStep(stepCount);

#if !defined(BENCHMARK)
    cout << "Done ! The first synchronized flash happened after " << stepCount << " steps." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_SecondPart()
{
    m_rowSize = 0;
    m_energyLevelGrid.clear();
    return EErrorCode::NotImplemented;
}

void CChallenge_11::Simulate(int _count, int& _flashCount)
{
    for (int i = 0; i < _count; ++i)
    {
        SimulateStep(_flashCount);
    }

#ifdef _DEBUG
    // Display last grid state
    for (int row = 0; row < m_energyLevelGrid.size(); ++row)
    {
        for (int col = 0; col < m_rowSize; ++col)
        {
            cout << m_energyLevelGrid[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
#endif // _DEBUG
}

void CChallenge_11::FindFirstSynchronizedFlashStep(int& _stepCount)
{
    _stepCount = 1;
    const int octopusCount = m_energyLevelGrid.size() * m_rowSize;

    while (true)
    {
        int flashCount = 0;
        SimulateStep(flashCount);

        // Found it !
        if (flashCount == octopusCount)
            break;

        ++_stepCount;
    }
}

void CChallenge_11::SimulateStep(int& _flashCount)
{
    // Initialize flashing status grid with false
    Grid<bool> flashingStatus(m_energyLevelGrid.size(), Row<bool>(m_rowSize, false));

    // Increment all energy levels
    for (int row = 0; row < m_energyLevelGrid.size(); ++row)
    {
        for (int col = 0; col < m_rowSize; ++col)
        {
            IncrementEnergyLevel(row, col, flashingStatus, _flashCount);
        }
    }
}

void CChallenge_11::IncrementEnergyLevel(int row, int col, Grid<bool>& _flashingStatus, int& _flashCount)
{
    // No increment if octopus has already flashed during this step
    if (_flashingStatus[row][col])
        return;

    // Increment energy level
    int& energyLevel = m_energyLevelGrid[row][col];
    if (energyLevel < 9)
    {
        ++energyLevel;
        return;
    }

    // Energy level is at its max. Set it to 0 and flash
    energyLevel = 0;
    _flashingStatus[row][col] = true;
    ++_flashCount;

    // Increment all adjacent octopuses
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        int nextRow = row + rowOffset;
        if (nextRow < 0 || nextRow >= m_energyLevelGrid.size())
            continue;

        for (int colOffset = -1; colOffset <= 1; ++colOffset)
        {
            int nextCol = col + colOffset;
            if (nextCol < 0 || nextCol >= m_rowSize || (rowOffset == 0 && colOffset == 0))
                continue;

            IncrementEnergyLevel(nextRow, nextCol, _flashingStatus, _flashCount);
        }
    }
}
