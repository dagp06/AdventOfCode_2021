#pragma once

#include "Common/Challenge.h"
#include <map>

using namespace std;

class CChallenge_8 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    // Part 1
    vector<string> m_inputLines;

    // Part 2
    class Entry
    {
    public:
        Entry(const vector<string>& _input, const vector<string>& _output) : m_input(_input), m_output(_output) {}

        int Solve();
        void SolveRemapping();
        void Remap(const string& _output, string& _outRealSignals);


    private:
        vector<string> m_input;
        vector<string> m_output;

        map<int, int> m_inputNumberIndices;

        typedef char Signal;
        map<Signal, Signal> m_signalRemapping; // Key : current signal, Value : real signal

        static const map<string, int> ms_signalToNumber;
    };

    vector<Entry> m_entries;
};
