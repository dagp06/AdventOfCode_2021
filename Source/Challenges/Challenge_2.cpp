#include "Challenge_2.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_2::sm_inputFilePath = "Inputs/Input_Challenge_2.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_2::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_commandStrings);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_2::Run_FirstPart()
{
    int horizontalPos = 0;
    int depth = 0;
    for (std::string& line : m_commandStrings)
    {
        std::vector<std::string> args;
        FileHelper::SplitLine(line, " ", args);
        int units = std::stoi(args[1]);
        if (args[0] == "forward")
        {
            horizontalPos += units;
        }
        else
        {
            depth += (args[0] == "up" ? -1 : 1) * units;
        }
    }

    std::cout << "Done ! Final pos : (" << horizontalPos<< ", " << depth << ")" << std::endl;
    std::cout << horizontalPos << " x " << depth << " = " << horizontalPos * depth << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_2::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_2::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_commandStrings);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_2::Run_SecondPart()
{
    long long horizontalPos = 0;
    long long depth = 0;
    long long aim = 0;
    for (std::string& line : m_commandStrings)
    {
        std::vector<std::string> args;
        FileHelper::SplitLine(line, " ", args);
        int units = std::stoi(args[1]);
        if (args[0] == "forward")
        {
            horizontalPos += units;
            depth += aim * units;
        }
        else
        {
            aim += (args[0] == "up" ? -1 : 1) * units;
        }
    }

    std::cout << "Done ! Final pos : (" << horizontalPos << ", " << depth << ")" << std::endl;
    std::cout << horizontalPos << " x " << depth << " = " << horizontalPos * depth << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_2::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}
