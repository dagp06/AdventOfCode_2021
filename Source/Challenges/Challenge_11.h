#pragma once

#include "Common/Challenge.h"

using namespace std;

class CChallenge_11 : public CChallenge
{
private:
    template<typename T>
    using Row = vector<T>;
    template<typename T>
    using Grid = vector<Row<T>>;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void Simulate(int _count, int& _flashCount);
    void SimulateStep(int& _flashCount);
    void IncrementEnergyLevel(int row, int col, Grid<bool>& _flashingStatus, int& _flashCount);
    void FindFirstSynchronizedFlashStep(int& _stepCount);

    static string const sm_inputFilePath;
    
    int m_rowSize = 0;
    Grid<int> m_energyLevelGrid;
};
