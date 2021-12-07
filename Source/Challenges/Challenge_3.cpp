#include "Challenge_3.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_3::sm_inputFilePath = "Inputs/Input_Challenge_3.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_3::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);

    if (readErrorCode != EErrorCode::Success)
        return readErrorCode;

    m_bitCount = (int)lines[0].size();
    for (std::string& line : lines)
    {
        m_numbers.push_back(std::stoi(line, nullptr, 2));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_3::Run_FirstPart()
{
    std::vector<int> ones;
    ones.resize(m_bitCount);

    for (const int& number : m_numbers)
    {
        for (int i = 0; i < m_bitCount; i++)
        {
            if (GetBitValue(number, i) == 1)
                ++ones[i];
        }
    }

    int halfNumbersCount = (int)m_numbers.size() / 2;
    int gammaRate = 0;
    int epsilonRate = 0;
    for (int i = 0; i < m_bitCount; ++i)
    {
        if (ones[i] >= halfNumbersCount)
        {
            SetBitValue(gammaRate, i);
        }
        else
        {
            SetBitValue(epsilonRate, i);
        }
    }

    int powerConsumption = gammaRate * epsilonRate;

    std::cout << "Done ! The power consumption is " << powerConsumption << "." << std::endl;

    if (powerConsumption == 0)
        std::cout << "Something went wrong !" << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_3::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_3::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);

    if (readErrorCode != EErrorCode::Success)
        return readErrorCode;

    m_bitCount = (int)lines[0].size();
    for (std::string& line : lines)
    {
        m_numbers.push_back(std::stoi(line, nullptr, 2));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_3::Run_SecondPart()
{
    std::vector<int> ones;
    ones.resize(m_bitCount);

    for (const int& number : m_numbers)
    {
        for (int i = 0; i < m_bitCount; i++)
        {
            if (GetBitValue(number, i) == 1)
                ++ones[i];
        }
    }

    int oxygenGeneratorRating = ApplyBitCriteria(m_numbers, ones, m_bitCount - 1, &OxygenBitCriteria);
    int co2ScrubberRating = ApplyBitCriteria(m_numbers, ones, m_bitCount - 1, &CarbonBitCriteria);

    int lifeSupportRating = oxygenGeneratorRating * co2ScrubberRating;
    std::cout << "Done !" << "The life support rating is " << lifeSupportRating << std::endl;

    if (lifeSupportRating == 0)
        std::cout << "Something went wrong !" << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_3::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

int CChallenge_3::GetBitValue(int _number, int _pos)
{
    return _number & (1 << _pos) ? 1 : 0;
}

void CChallenge_3::SetBitValue(int& _number, int _pos)
{
    _number |= (1 << _pos);
}

int CChallenge_3::ApplyBitCriteria(std::vector<int> _numbers, std::vector<int> _ones, int _currentBit, CChallenge_3::BitCriteria _bitCriteria)
{
    int bitToKeep = _bitCriteria(_ones[_currentBit], (int)_numbers.size());

    std::vector<int>::iterator it = _numbers.begin();
    while (it != _numbers.end())
    {
        int number = (*it);
        if (bitToKeep != GetBitValue(number, _currentBit))
        {
            // Current bit doesn't match bit criteria.
            // Remove it from _numbers and update _ones.
            it = _numbers.erase(it);

            for (int i = 0; i < m_bitCount; ++i)
            {
                if (GetBitValue(number, i) == 1)
                {
                    --_ones[i];
                }
            }
        }
        else
        {
            // Current bit matches bit criteria, keep number and keep going.
            ++it;
        }
    };

    
    if (_numbers.size() == 1)
    {
        // We're done !
        return _numbers[0];
    }

    if (_numbers.empty() || _currentBit == 0)
    {
        // Something went wrong !
        return 0;
    }

    // Keep going !
    return ApplyBitCriteria(_numbers, _ones, --_currentBit, _bitCriteria);
}

int CChallenge_3::OxygenBitCriteria(int _ones, int _numbersCount)
{
    if (_numbersCount == 0)
    {
        // Something went wrong !
        return -1;
    }

    return (float)_ones / _numbersCount >= 0.5f ? 1 : 0;
}

int CChallenge_3::CarbonBitCriteria(int _ones, int _numbersCount)
{
    if (_numbersCount == 0)
    {
        // Something went wrong !
        return -1;
    }

    return (float)_ones / _numbersCount < 0.5f ? 1 : 0;
}
