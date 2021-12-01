#include "Challenge_1.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_1::sm_inputFilePath = "Inputs/Input_Challenge_1.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_1::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_1::Run_FirstPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_1::CleanUp_FirstPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_1::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_1::Run_SecondPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_1::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}
