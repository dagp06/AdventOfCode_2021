#include "Challenge_14.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_14::sm_inputFilePath = "Inputs/Input_Challenge_14.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Store pairs and elements' counts
    const string& polymerString = lines[0];
    ElemPair pair;
    for (int i = 0; i < polymerString.size() - 1; ++i)
    {
        pair = ElemPair(polymerString[i], polymerString[i + 1]);
        ++m_polymerPairCounts[pair];
        ++m_polymerElemCount[pair.first];
    }
    ++m_polymerElemCount[pair.second];

    // Store pair insertion rules
    for (int i = 2; i < lines.size(); ++i)
    {
        const string& ruleString = lines[i];
        vector<string> args;
        FileHelper::SplitLine(ruleString, " -> ", args);

        // Instead of storing the whole polymer, let's just store each pair to evaluate and their amount in the polymer.
        // Each rule inserts an element in the polymer when the key pair is met
        // e.g. XY -> Z
        // That means next iteration, we will have 2 new pairs to evaluate. : XZ and XY.
        // The keypair that was read, XY, won't be in the next iteration either, so we'll have to reduce its count.
        ElemPair keyPair(args[0][0], args[0][1]);
        ElemPair firstPairToInsert(args[0][0], args[1][0]);
        ElemPair secondPairToInsert(args[1][0], args[0][1]);
        m_pairInsertionRules[keyPair] = vector<ElemPair>({ firstPairToInsert, secondPairToInsert });
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::Run_FirstPart()
{
    unsigned long long result = RunPairInsertionProcess(10);

#if !defined(BENCHMARK)
    cout << "Done ! By substracting the most and least common element counts, we get " << result << "." << endl;
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_FirstPart()
{
    m_polymerElemCount.clear();
    m_polymerPairCounts.clear();
    m_pairInsertionRules.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    const string& polymerString = lines[0];
    ElemPair pair;
    for (int i = 0; i < polymerString.size() - 1; ++i)
    {
        pair = ElemPair(polymerString[i], polymerString[i + 1]);
        ++m_polymerPairCounts[pair];
        ++m_polymerElemCount[pair.first];
    }
    ++m_polymerElemCount[pair.second];

    for (int i = 2; i < lines.size(); ++i)
    {
        const string& ruleString = lines[i];
        vector<string> args;
        FileHelper::SplitLine(ruleString, " -> ", args);
        
        ElemPair keyPair(args[0][0], args[0][1]);
        ElemPair firstPairToInsert(args[0][0], args[1][0]);
        ElemPair secondPairToInsert(args[1][0], args[0][1]);
        m_pairInsertionRules[keyPair] = vector<ElemPair>({ firstPairToInsert, secondPairToInsert });
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::Run_SecondPart()
{
    unsigned long long result = RunPairInsertionProcess(40);

#if !defined(BENCHMARK)
    cout << "Done ! By substracting the most and least common element counts, we get " << result << "." << endl;
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_SecondPart()
{
    m_polymerElemCount.clear();
    m_polymerPairCounts.clear();
    m_pairInsertionRules.clear();
    return EErrorCode::Success;
}


unsigned long long CChallenge_14::RunPairInsertionProcess(int _stepCount)
{
    for (int i = 1; i <= _stepCount; ++i)
    {
#if !defined(BENCHMARK)
        cout << "Running iteration " << i << "..." << endl;
#endif
        // Store pairs to add/remove and edit m_polymerPairCounts after the iteration,
        // so we don't count added pairs / omit to count removed pairs
        map<ElemPair, unsigned long long> pairsToAdd;
        map<ElemPair, unsigned long long> pairsToRemove;
        for (auto it = m_polymerPairCounts.begin(); it != m_polymerPairCounts.end(); ++it)
        {
            const unsigned long long& currentPairCount = (*it).second;
            if (currentPairCount == 0)
                continue;

            const ElemPair& currentPair = (*it).first;
            auto pairRuleIt = m_pairInsertionRules.find(currentPair);
            if (pairRuleIt == m_pairInsertionRules.end())
                continue;

            const vector<ElemPair>& currentPairsToAdd = (*pairRuleIt).second;

            // Count newly added element.
            // It's the first pair to add's second element
            // e.g. XY -> Z generates XZ and ZY. The new character is Z, XZ's second element.
            m_polymerElemCount[currentPairsToAdd[0].second] += currentPairCount;

            for (const ElemPair& pair : currentPairsToAdd)
            {
                pairsToAdd[pair] += currentPairCount;
            }

            pairsToRemove[currentPair] += currentPairCount;
        }

        for (const auto& pair : pairsToAdd)
        {
            m_polymerPairCounts[pair.first] += pair.second;
        }

        for (const auto& pair : pairsToRemove)
        {
            m_polymerPairCounts[pair.first] -= pair.second;
        }
    }

    // Find least and most common characters
    unsigned long long leastCommonCharacterCount = ULLONG_MAX;
    unsigned long long mostCommonCharacterCount = 0;
    for (auto it = m_polymerElemCount.begin(); it != m_polymerElemCount.end(); ++it)
    {
        leastCommonCharacterCount = min(leastCommonCharacterCount, (*it).second);
        mostCommonCharacterCount = max(mostCommonCharacterCount, (*it).second);
    }

    // Return their difference
    return mostCommonCharacterCount - leastCommonCharacterCount;
}
