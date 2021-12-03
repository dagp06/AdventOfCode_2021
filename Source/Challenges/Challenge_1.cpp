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

    for (std::string& line : lines)
    {
        m_depths.push_back(std::stoi(line));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_1::Run_FirstPart()
{
    int depthIncreaseCount = 0;
    for (int i = 1; i < m_depths.size(); ++i)
    {
        depthIncreaseCount += m_depths[i - 1] < m_depths[i] ? 1 : 0;
    }

    std::cout << "Done ! There are " << depthIncreaseCount << " depths increases." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_1::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_1::SetUp_SecondPart()
{
    return SetUp_FirstPart();
}

EErrorCode CChallenge_1::Run_SecondPart()
{
    if (m_depths.size() < m_windowSize + 1)
    {
        std::cout << "Not enough depth readings to compute and compare two windows." << std::endl;
        return EErrorCode::Success;
    }

    int depthWindowIncreaseCount = 0;
    for (int i = 0; i < m_depths.size() - m_windowSize; ++i)
    {
        if (m_depths[i] < m_depths[i + m_windowSize])
            ++depthWindowIncreaseCount;
    }

    std::cout << "Done ! There are " << depthWindowIncreaseCount << " depths increases." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_1::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}
