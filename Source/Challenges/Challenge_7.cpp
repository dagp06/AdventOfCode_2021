#include "Challenge_7.h"
#include "../Helpers/FileHelpers.h"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_7::sm_inputFilePath = "Inputs/Input_Challenge_7.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_7::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    vector<string> posStrings;
    FileHelper::SplitLine(lines[0], ",", posStrings);

    for (const string& posString : posStrings)
    {
        m_horizontalPosSet.insert(stoi(posString));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_7::Run_FirstPart()
{
    int medianPos = (int)m_horizontalPosSet.size() / 2 - 1;
    int median = *next(m_horizontalPosSet.begin(), medianPos);

    long long fuelConsumed = ComputeTotalFuelConsumed(median, true);

#if !defined(BENCHMARK)
    cout << "Done ! Crabs will alling on pos " << median << " and consume a total of " << fuelConsumed << " fuel." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_7::CleanUp_FirstPart()
{
    m_horizontalPosSet.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_7::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    vector<string> posStrings;
    FileHelper::SplitLine(lines[0], ",", posStrings);

    long long sum = 0ll;
    for (const string& posString : posStrings)
    {
        int pos = stoi(posString);
        sum += pos;
        m_horizontalPosSet.insert(pos);
    }

    m_lowMeanPos = (int)floor(sum / (float)m_horizontalPosSet.size());
    
    return EErrorCode::Success;
}

EErrorCode CChallenge_7::Run_SecondPart()
{
    long long fuelConsumedLowMean = ComputeTotalFuelConsumed(m_lowMeanPos, false);
    long long fuelConsumedHighMean = ComputeTotalFuelConsumed(m_lowMeanPos + 1, false);

    bool lowMeanIsMoreEfficient = fuelConsumedLowMean < fuelConsumedHighMean;


#if !defined(BENCHMARK)
    cout << "Done ! Crabs will alling on pos " << m_lowMeanPos + (lowMeanIsMoreEfficient ? 0 : 1) << " and consume a total of " << (lowMeanIsMoreEfficient ? fuelConsumedLowMean : fuelConsumedHighMean) << " fuel." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_7::CleanUp_SecondPart()
{
    m_horizontalPosSet.clear();
    m_lowMeanPos = 0;
    return EErrorCode::Success;
}

long long CChallenge_7::ComputeTotalFuelConsumed(int _pos, bool _constantCost) const
{
    long long fuelConsumed = 0ll;
    for (const int& horizontalPos : m_horizontalPosSet)
    {
        fuelConsumed += ComputeFuelConsumed(abs(horizontalPos - _pos), _constantCost);
    }

    return fuelConsumed;
}

long long CChallenge_7::ComputeFuelConsumed(int _distance, bool _constantCost)
{
    if (_constantCost)
    {
        return _distance;
    }
    else
    {
        return (_distance * (_distance + 1)) / 2;
    }
    return 0;
}
