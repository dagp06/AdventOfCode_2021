#pragma once

#include "Common/Challenge.h"
#include <map>

class CChallenge_4 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;

    typedef std::vector<int> BingoRow;
    typedef std::vector<BingoRow> BingoCard;

    static const int sm_cardSize = 5;
    std::vector<int> m_numbers;
    std::map<int, int> m_drawOrderMap;
    std::vector<BingoCard> m_bingoCards;
};
