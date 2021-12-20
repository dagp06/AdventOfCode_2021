#include "Challenge_8.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <set>

////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_8::sm_inputFilePath = "Inputs/Input_Challenge_8.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_8::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_inputLines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }


    return EErrorCode::Success;
}

EErrorCode CChallenge_8::Run_FirstPart()
{
    int count = 0;

    vector<string> entrySplit;
    entrySplit.reserve(2);
    vector<string> outputSplit;
    outputSplit.reserve(4);
    for (const string& line : m_inputLines)
    {
        FileHelper::SplitLine(line, " | ", entrySplit);
        FileHelper::SplitLine(entrySplit[1], " ", outputSplit);

        for (const string& outputValue : outputSplit)
        {
            int size = (int)outputValue.size();
            if (size == 2 || size == 3 || size == 4 || size == 7)
            {
                ++count;
            }
        }

        entrySplit.clear();
        outputSplit.clear();
    }

#if !defined(BENCHMARK)
    cout << "Done ! Digits 1, 4, 7 and 8 appear " << count << " times in the output values." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_8::CleanUp_FirstPart()
{
    m_inputLines.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_8::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    vector<string> entrySplit;
    entrySplit.reserve(2);
    vector<string> inputSplit;
    inputSplit.reserve(10);
    vector<string> outputSplit;
    outputSplit.reserve(4);
    for (const string& line : lines)
    {
        FileHelper::SplitLine(line, " | ", entrySplit);
        FileHelper::SplitLine(entrySplit[0], " ", inputSplit);
        FileHelper::SplitLine(entrySplit[1], " ", outputSplit);

        m_entries.push_back(Entry(inputSplit, outputSplit));

        entrySplit.clear();
        inputSplit.clear();
        outputSplit.clear();
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_8::Run_SecondPart()
{
    int outputValuesSum = 0;

    for (Entry& entry : m_entries)
    {
        outputValuesSum += entry.Solve();
    }

#if !defined(BENCHMARK)
    cout << "Done ! The sum of all output values is " << outputValuesSum << "." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_8::CleanUp_SecondPart()
{
    m_entries.clear();
    return EErrorCode::Success;
}

const map<string, int> CChallenge_8::Entry::ms_signalToNumber =
{
    {"abcefg", 0},
    {"cf", 1},
    {"acdeg", 2},
    {"acdfg", 3},
    {"bcdf", 4},
    {"abdfg", 5},
    {"abdefg", 6},
    {"acf", 7},
    {"abcdefg", 8},
    {"abcdfg", 9},
};

int CChallenge_8::Entry::Solve()
{
    SolveRemapping();
    
    int outputValue = 0;
    string realSignal;
    for (string& output : m_output)
    {
        Remap(output, realSignal);
        sort(realSignal.begin(), realSignal.end());
        const int& value = ms_signalToNumber.at(realSignal);

#if !defined(BENCHMARK)
        cout << " = " << value << endl;
#endif // !BENCHMARK
        
        outputValue += value;
        outputValue *= 10;
    }
    
    return outputValue / 10;
}

void CChallenge_8::Entry::SolveRemapping()
{
    set<Signal> signalsToIdentify{ 'a', 'b', 'c', 'd', 'e', 'f', 'g' };

    // Find #1, #4, #7 and #8.
    for (int i = 0; i < m_input.size(); ++i)
    {
        // #1
        if (m_input[i].size() == 2)
        {
            m_inputNumberIndices[1] = i;
            continue;
        }

        // #7
        if (m_input[i].size() == 3)
        {
            m_inputNumberIndices[7] = i;
            continue;
        }

        // #4
        if (m_input[i].size() == 4)
        {
            m_inputNumberIndices[4] = i;
            continue;
        }

        // #8
        if (m_input[i].size() == 7)
        {
            m_inputNumberIndices[8] = i;
            continue;
        }
    }

    // Compare #1 to #7 to figure out a.
    const string& input1 = m_input[m_inputNumberIndices[1]];
    const string& input7 = m_input[m_inputNumberIndices[7]];
    for (const Signal& signal : input7)
    {
        // #1's signal not found in #7 is a.
        if (input1.find(signal) == string::npos)
        {
            m_signalRemapping[signal] = 'a';
            signalsToIdentify.erase(signal);
            break;
        }
    }

    // Find #6. It's the only 6 signal-number that doesn't have all #1 signals.
    for (int i = 0; i < m_input.size(); ++i)
    {
        const string& number = m_input[i];
        if (number.size() != 6)
            continue;

        bool found = false;
        for (const Signal& signal : input1)
        {
            if (number.find(signal) == string::npos)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            m_inputNumberIndices[6] = i;
            break;
        }
    }

    // Find #5 and figure out e. It's the only 5 signal-number that has all but one of #6's signals (e).
    const string& input6 = m_input[m_inputNumberIndices[6]];
    for (int i = 0; i < m_input.size(); ++i)
    {
        const string& number = m_input[i];
        if (number.size() != 5)
            continue;

        int missingSignalCount = 0;
        Signal missingSignal;
        for (const Signal& signal : input6)
        {
            if (number.find(signal) == string::npos)
            {
                if (++missingSignalCount == 2)
                    break;
                else
                    missingSignal = signal;
            }
        }

        if (missingSignalCount == 1)
        {
            m_inputNumberIndices[5] = i;
            m_signalRemapping[missingSignal] = 'e';
            signalsToIdentify.erase(missingSignal);
            break;
        }
    }

    // Compare #1 to #5 to figure out c and f.
    // The signal from #1 that can't be found in #5 is c. The other one is f.
    const string& input5 = m_input[m_inputNumberIndices[5]];
    if (input5.find(input1[0]) == string::npos)
    {
        m_signalRemapping[input1[0]] = 'c';
        m_signalRemapping[input1[1]] = 'f';
    }
    else
    {
        m_signalRemapping[input1[1]] = 'c';
        m_signalRemapping[input1[0]] = 'f';
    }
    signalsToIdentify.erase(input1[0]);
    signalsToIdentify.erase(input1[1]);

    // Find #2. It's the 5-signal number that isn't #5 and doesn't have all of #1's signals.
    for (int i = 0; i < m_input.size(); ++i)
    {
        const string& number = m_input[i];
        if (number.size() != 5 || i == m_inputNumberIndices[5])
            continue;

        bool found = false;
        for (const Signal& signal : input1)
        {
            if (number.find(signal) == string::npos)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            m_inputNumberIndices[2] = i;
            break;
        }
    }

    // Compare #4 to #2 and #1 to figure out b and d
    const string& input2 = m_input[m_inputNumberIndices[2]];
    const string& input4 = m_input[m_inputNumberIndices[4]];
    for (const Signal& signal : input4)
    {
        // Among the signals from #4 that are not in #1...
        if (input1.find(signal) == string::npos)
        {
            // The one that isn't in #2 is b
            if (input2.find(signal) == string::npos)
            {
                m_signalRemapping[signal] = 'b';
                signalsToIdentify.erase(signal);
            }
            // The one that is in #2 is d
            else
            {
                m_signalRemapping[signal] = 'd';
                signalsToIdentify.erase(signal);
            }
        }
    }

    // Last one is g !
    m_signalRemapping[*signalsToIdentify.begin()] = 'g';
}

void CChallenge_8::Entry::Remap(const string& _output, string& _outRealSignals)
{
    _outRealSignals.clear();
    _outRealSignals.reserve(_output.size());
    for (const Signal& signal : _output)
    {
        _outRealSignals.push_back(m_signalRemapping.at(signal));
    }

#if !defined(BENCHMARK)
    cout << _output << " --> " << _outRealSignals;
#endif // !BENCHMARK
}
