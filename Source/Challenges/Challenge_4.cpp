#include "Challenge_4.h"
#include "../Helpers/FileHelpers.h"
#include <sstream>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_4::sm_inputFilePath = "Inputs/Input_Challenge_4.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_4::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Read drawn numbers
    std::vector<std::string> numbers;
    FileHelper::SplitLine(lines[0], ",", numbers);
    /*for (const std::string& number : numbers)
    {
        m_numbers.push_back(std::stoi(number));
    }*/

    for (int i = 0; i < numbers.size(); ++i)
    {
        m_drawOrderMap[std::stoi(numbers[i])] = i;
    }

    // Read bingo cards
    for (int i = 2; i < lines.size(); i += (sm_cardSize + 1))
    {
        m_bingoCards.push_back(BingoCard(sm_cardSize, BingoRow(sm_cardSize)));
        BingoCard& bingoCard = m_bingoCards[m_bingoCards.size() - 1];
        ;
        for (int j = 0; j < sm_cardSize; ++j)
        {
            BingoRow& bingoRow = bingoCard[j];

            std::stringstream ss;
            ss << lines[i + j];

            int k = 0;
            std::string temp;
            int number = 0;
            while (!ss.eof() && k < sm_cardSize)
            {
                ss >> temp;

                if (std::stringstream(temp) >> number)
                {
                    bingoRow[k] = number;
                    ++k;
                }

                temp = "";
            }
        }

        m_bingoCards.push_back(bingoCard);
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::Run_FirstPart()
{
    const BingoCard* firstBingoCardToFinish = nullptr;
    int lastNumberPicked = 0; // need dis
    
    int lowestLineSum = INT_MAX;
    for (const BingoCard& bingoCard : m_bingoCards)
    {
        int lowestCardLineSum = INT_MAX;
        for (int i = 0; i < sm_cardSize; ++i)
        {
            int rowSum = 0;
            int colSum = 0;
            for (int j = 0; j < sm_cardSize; ++j)
            {
                rowSum += m_drawOrderMap[bingoCard[i][j]];
                colSum += m_drawOrderMap[bingoCard[j][i]];
            }
            lowestCardLineSum = std::min(lowestCardLineSum, std::min(rowSum, colSum));
        }

        if (lowestCardLineSum < lowestLineSum)
        {
            lowestLineSum = lowestCardLineSum;
            firstBingoCardToFinish = &bingoCard;
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_4::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_4::Run_SecondPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_4::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}
