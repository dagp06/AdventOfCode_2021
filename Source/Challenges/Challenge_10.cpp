#include "Challenge_10.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <stack>

////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_10::sm_inputFilePath = "Inputs/Input_Challenge_10.txt";
map<char, char> const CChallenge_10::sm_characterPairs = { {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
map<char, int> const CChallenge_10::sm_syntaxCheckerPoints = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
map<char, long long> const CChallenge_10::sm_autocompleteToolPoints = { {')', 1ll}, {']', 2ll}, {'}', 3ll}, {'>', 4ll} };


////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_navigationLines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::Run_FirstPart()
{
    int syntaxErrorScore = 0;

    for (const string& line : m_navigationLines)
    {
        stack<char> characterStack;
        for (const char& character : line)
        {
            if (IsOpeningCharacter(character))
            {
                characterStack.push(character);
            }
            else if (!characterStack.empty() && sm_characterPairs.at(characterStack.top()) == character)
            {
                characterStack.pop();
            }
            else
            {
#if defined(_DEBUG)
                if (characterStack.empty())
                {
                    cout << "Expected an opening character, but found " << character << " instead." << endl;
                }
                else
                {
                    cout << "Expected " << sm_characterPairs.at(characterStack.top()) << ", but found " << character << " instead." << endl;
                }
#endif // _DEBUG
                syntaxErrorScore += sm_syntaxCheckerPoints.at(character);
                break;
            }
        }
    }

#if !defined(BENCHMARK)
    cout << "Done ! The syntax error score is " << syntaxErrorScore << "." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::CleanUp_FirstPart()
{
    m_navigationLines.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_navigationLines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::Run_SecondPart()
{
    vector<long long> autompletionScores;

    for (const string& line : m_navigationLines)
    {
        long long autocompletionScore = 0;
        stack<char> characterStack;
        bool isCorrupted = false;
        for (const char& character : line)
        {
            if (IsOpeningCharacter(character))
            {
                characterStack.push(character);
            }
            else if (!characterStack.empty() && sm_characterPairs.at(characterStack.top()) == character)
            {
                characterStack.pop();
            }
            else
            {
                isCorrupted = true;
                break;
            }
        }
        if (isCorrupted)
            continue;

        while(!characterStack.empty())
        {
            autocompletionScore *= 5ll;
            autocompletionScore += sm_autocompleteToolPoints.at(sm_characterPairs.at(characterStack.top()));
            characterStack.pop();
        }

#if defined(_DEBUG)
        cout << line << " - " << autocompletionScore << " total points." << endl;
#endif // _DEBUG


        autompletionScores.push_back(autocompletionScore);
    }

    sort(autompletionScores.begin(), autompletionScores.end());

#if !defined(BENCHMARK)
    cout << "Done ! The autocomplete score is " << autompletionScores[autompletionScores.size() / 2] << "." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::CleanUp_SecondPart()
{
    m_navigationLines.clear();
    return EErrorCode::Success;
}
