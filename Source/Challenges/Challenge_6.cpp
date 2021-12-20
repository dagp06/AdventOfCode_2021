#include "Challenge_6.h"
#include "../Helpers/FileHelpers.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_6::sm_inputFilePath = "Inputs/Input_Challenge_6.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_6::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Initialize an entry to 0 for each possible timer value
    m_lanternfishCountPerTimerValue.resize(ms_firstCycleDuration, 0ll);

    vector<string> timerStrings;
    FileHelper::SplitLine(lines[0], ",", timerStrings);
    for (const string& timerString : timerStrings)
    {
        ++m_lanternfishCountPerTimerValue[stoi(timerString)];
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_6::Run_FirstPart()
{
    Simulate(80);

    long long lanternFishCount = ComputeTotalLanternfish();

#if !defined(BENCHMARK)
    cout << "Done ! After 80 days, there would be " << lanternFishCount << " lanternfish." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_6::CleanUp_FirstPart()
{
    m_lanternfishCountPerTimerValue.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_6::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Initialize an entry to 0 for each possible timer value
    m_lanternfishCountPerTimerValue.resize(ms_firstCycleDuration, 0ll);

    vector<string> timerStrings;
    FileHelper::SplitLine(lines[0], ",", timerStrings);
    for (const string& timerString : timerStrings)
    {
        ++m_lanternfishCountPerTimerValue[stoi(timerString)];
    }
    
    return EErrorCode::Success;
}

EErrorCode CChallenge_6::Run_SecondPart()
{
    Simulate(256);

    long long lanternFishCount = ComputeTotalLanternfish();

#if !defined(BENCHMARK)
    cout << "Done ! After 256 days, there would be " << lanternFishCount << " lanternfish." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_6::CleanUp_SecondPart()
{
    m_lanternfishCountPerTimerValue.clear();
    return EErrorCode::Success;
}

void CChallenge_6::Simulate(int _days)
{
    // Everyday, each entry's value is shifted to the left.
    // The only entry that gets a modification is the one at the "cycle duration" 's index, to which we add the fish count of the entry for index 0.
    for (int day = 0; day < _days; ++day)
    {
        m_lanternfishCountPerTimerValue[GetIndexForDay(ms_cycleDuration, day)] += m_lanternfishCountPerTimerValue[GetIndexForDay(0, day)];
    }
}

long long CChallenge_6::ComputeTotalLanternfish() const
{
    long long lanternFishCount = 0ll;
    for (const long long& lanternfishCount : m_lanternfishCountPerTimerValue)
    {
        lanternFishCount += lanternfishCount;
    }

    return lanternFishCount;
}

int CChallenge_6::GetIndexForDay(const int& _index, const int& _day) const
{
    return (_index + _day) % ms_firstCycleDuration;
}
