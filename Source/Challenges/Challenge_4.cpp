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
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::Run_FirstPart()
{
    // Find first card to finish
    const BingoCard* firstBingoCardToFinish = nullptr;
    int lastPickedIdx = INT_MAX;
    for (const BingoCard& bingoCard : m_bingoCards)
    {
        int currentLowestLastPickedIdx = INT_MAX;
        for (int i = 0; i < sm_cardSize; ++i)
        {
            int rowLastPickedIdx = 0;
            int colLastPickedIdx = 0;
            for (int j = 0; j < sm_cardSize; ++j)
            {
                rowLastPickedIdx = std::max(rowLastPickedIdx, m_drawOrderMap[bingoCard[i][j]]);
                colLastPickedIdx = std::max(colLastPickedIdx, m_drawOrderMap[bingoCard[j][i]]);
            }
            currentLowestLastPickedIdx = std::min(currentLowestLastPickedIdx, std::min(rowLastPickedIdx, colLastPickedIdx));
        }

        if (currentLowestLastPickedIdx < lastPickedIdx)
        {
            lastPickedIdx = currentLowestLastPickedIdx;
            firstBingoCardToFinish = &bingoCard;
        }
    }

    if (firstBingoCardToFinish == nullptr)
    {
        std::cout << "Error : Did not find the last bingo card to finish. Aborting." << std::endl;
        return EErrorCode::Undefined;
    }

#if !defined(BENCHMARK)
    std::cout << "First bingo card to finish :" << std::endl;
    PrintBingoCard(*firstBingoCardToFinish);
#endif // !BENCHMARK

    // Sum all numbers that were not picked
    int unmarkedNumbersSum = 0;
    int lastNumberPicked = 0;
    for (int i = 0; i < sm_cardSize; ++i)
    {
        for (int j = 0; j < sm_cardSize; ++j)
        {
            int number = (*firstBingoCardToFinish)[i][j];
            int numberIdx = m_drawOrderMap[number];
            
            if (numberIdx > lastPickedIdx)
            {
                unmarkedNumbersSum += number;
            }
            else if (numberIdx == lastPickedIdx)
            {
                lastNumberPicked = number;
            }
        }
    }

    int score = unmarkedNumbersSum * lastNumberPicked;

#if !defined(BENCHMARK)
    std::cout << "Last index picked :" << lastPickedIdx << std::endl;
    std::cout << "Last number picked :" << lastNumberPicked << std::endl;
    // Multiply by last picked number

    std::cout << "Done !" << "The score is " << score << std::endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::CleanUp_FirstPart()
{
    m_bingoCards.clear();
    m_drawOrderMap.clear();
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

    // Read drawn numbers
    std::vector<std::string> numbers;
    FileHelper::SplitLine(lines[0], ",", numbers);

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
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::Run_SecondPart()
{
    // Find first card to finish
    const BingoCard* lastBingoCardToFinish = nullptr;
    int lastPickedIdx = 0;
    for (const BingoCard& bingoCard : m_bingoCards)
    {
        int currentLowestLastPickedIdx = INT_MAX;
        for (int i = 0; i < sm_cardSize; ++i)
        {
            int rowLastPickedIdx = 0;
            int colLastPickedIdx = 0;
            for (int j = 0; j < sm_cardSize; ++j)
            {
                rowLastPickedIdx = std::max(rowLastPickedIdx, m_drawOrderMap[bingoCard[i][j]]);
                colLastPickedIdx = std::max(colLastPickedIdx, m_drawOrderMap[bingoCard[j][i]]);
            }
            currentLowestLastPickedIdx = std::min(currentLowestLastPickedIdx, std::min(rowLastPickedIdx, colLastPickedIdx));
        }

        if (currentLowestLastPickedIdx > lastPickedIdx)
        {
            lastPickedIdx = currentLowestLastPickedIdx;
            lastBingoCardToFinish = &bingoCard;
        }
    }

    if (lastBingoCardToFinish == nullptr)
    {
        std::cout << "Error : Did not find the last bingo card to finish. Aborting." << std::endl;
        return EErrorCode::Undefined;
    }

#if !defined(BENCHMARK)
    std::cout << "First bingo card to finish :" << std::endl;
    PrintBingoCard(*lastBingoCardToFinish);
#endif // !BENCHMARK

    // Sum all numbers that were not picked
    int unmarkedNumbersSum = 0;
    int lastNumberPicked = 0;
    for (int i = 0; i < sm_cardSize; ++i)
    {
        for (int j = 0; j < sm_cardSize; ++j)
        {
            int number = (*lastBingoCardToFinish)[i][j];
            int numberIdx = m_drawOrderMap[number];

            if (numberIdx > lastPickedIdx)
            {
                unmarkedNumbersSum += number;
            }
            else if (numberIdx == lastPickedIdx)
            {
                lastNumberPicked = number;
            }
        }
    }

    int score = unmarkedNumbersSum * lastNumberPicked;


#if !defined(BENCHMARK)
    std::cout << "Last index picked :" << lastPickedIdx << std::endl;
    std::cout << "Last number picked :" << lastNumberPicked << std::endl;
    // Multiply by last picked number

    std::cout << "Done !" << "The score is " << score << std::endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_4::CleanUp_SecondPart()
{
    m_bingoCards.clear();
    m_drawOrderMap.clear();
    return EErrorCode::Success;
}

void CChallenge_4::PrintBingoCard(const BingoCard& _bingoCard)
{
    for (int i = 0; i < sm_cardSize; ++i)
    {
        for (int j = 0; j < sm_cardSize; ++j)
        {
            int number = _bingoCard[i][j];
            std::cout << number << (number < 10 ? "  " : " ");
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void CChallenge_4::PrintBingoCardIndexes(const BingoCard& _bingoCard)
{
    BingoCard indexCard(sm_cardSize, BingoRow(sm_cardSize));
    for (int i = 0; i < sm_cardSize; ++i)
    {
        for (int j = 0; j < sm_cardSize; ++j)
        {
            indexCard[i][j] = m_drawOrderMap[_bingoCard[i][j]];
        }
    }

    PrintBingoCard(indexCard);
}
