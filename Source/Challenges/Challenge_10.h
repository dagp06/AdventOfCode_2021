#pragma once

#include "Common/Challenge.h"
#include <map>

using namespace std;

class CChallenge_10 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    bool IsOpeningCharacter(const char& _char) { return sm_characterPairs.find(_char) != sm_characterPairs.end(); }

    static string const sm_inputFilePath;
    static map<char, char> const sm_characterPairs;
    static map<char, int> const sm_syntaxCheckerPoints;
    static map<char, long long> const sm_autocompleteToolPoints;

    vector<string> m_navigationLines;
};
