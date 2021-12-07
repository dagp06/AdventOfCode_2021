#pragma once

#include "Common/Challenge.h"
#include <functional>

class CChallenge_3 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    typedef std::function<int(int, int)> BitCriteria;

    static int GetBitValue(int _number, int _pos);
    static void SetBitValue(int& _number, int _pos);
    static int OxygenBitCriteria(int _ones, int _numbersCount);
    static int CarbonBitCriteria(int _ones, int _numbersCount);

    int ApplyBitCriteria(std::vector<int> _numbers, std::vector<int> _ones, int _currentBit, BitCriteria _bitCriteria);


    static std::string const sm_inputFilePath;

    std::vector<int> m_numbers;
    int m_bitCount = 0;
};