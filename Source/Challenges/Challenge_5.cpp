#include "Challenge_5.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_5::sm_inputFilePath = "Inputs/Input_Challenge_5.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_5::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_inputLines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_5::Run_FirstPart()
{
    int overlappingVentCoordinateCount = 0;
    for (const string& line : m_inputLines)
    {
        vector<string> coordinateStrings;
        FileHelper::SplitLine(line, " -> ", coordinateStrings);

        vector<string> coordinate1Strings;
        FileHelper::SplitLine(coordinateStrings[0], ",", coordinate1Strings);
        Coordinate coordinate1(stoi(coordinate1Strings[0]), stoi(coordinate1Strings[1]));

        vector<string> coordinate2Strings;
        FileHelper::SplitLine(coordinateStrings[1], ",", coordinate2Strings);
        Coordinate coordinate2(stoi(coordinate2Strings[0]), stoi(coordinate2Strings[1]));

        if (coordinate1.X == coordinate2.X)
        {
            int startY = min(coordinate1.Y, coordinate2.Y);
            int endY = max(coordinate1.Y, coordinate2.Y);
            for (int i = startY; i <= endY; ++i)
            {
                if (++m_ventsLocations[Coordinate(coordinate1.X, i)] == 2)
                    ++overlappingVentCoordinateCount;
            }
        }
        else if (coordinate1.Y == coordinate2.Y)
        {
            int startX = min(coordinate1.X, coordinate2.X);
            int endX = max(coordinate1.X, coordinate2.X);
            for (int i = startX; i <= endX; ++i)
            {
                if (++m_ventsLocations[Coordinate(i, coordinate1.Y)] == 2)
                    ++overlappingVentCoordinateCount;
            }
        }
    }

#if !defined(BENCHMARK)
    cout << "Done ! Vent lines overlap at " << overlappingVentCoordinateCount << " points." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_5::CleanUp_FirstPart()
{
    m_inputLines.clear();
    m_ventsLocations.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_5::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_inputLines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_5::Run_SecondPart()
{
    int overlappingVentCoordinateCount = 0;
    int lineID = 0;
    for (const string& line : m_inputLines)
    {
        //cout << "Line " << ++lineID << "/500" << endl;
        vector<string> coordinateStrings;
        FileHelper::SplitLine(line, " -> ", coordinateStrings);

        vector<string> coordinate1Strings;
        FileHelper::SplitLine(coordinateStrings[0], ",", coordinate1Strings);
        Coordinate coordinate1(stoi(coordinate1Strings[0]), stoi(coordinate1Strings[1]));

        vector<string> coordinate2Strings;
        FileHelper::SplitLine(coordinateStrings[1], ",", coordinate2Strings);
        Coordinate coordinate2(stoi(coordinate2Strings[0]), stoi(coordinate2Strings[1]));

        bool isHorizontal = coordinate1.Y == coordinate2.Y;
        bool isVertical = coordinate1.X == coordinate2.X;
        int length = isHorizontal ? abs(coordinate1.X - coordinate2.X) : abs(coordinate1.Y - coordinate2.Y);
        bool isNegativeSlopeX = coordinate1.X > coordinate2.X;
        bool isNegativeSlopeY = coordinate1.Y > coordinate2.Y;
        
        for (int i = 0; i <= length; ++i)
        {
            int x = coordinate1.X + (isVertical ? 0 : (isNegativeSlopeX ? -i : i));
            int y = coordinate1.Y + (isHorizontal ? 0 : (isNegativeSlopeY ? -i : i));
            if (++m_ventsLocations[Coordinate(x, y)] == 2)
                    ++overlappingVentCoordinateCount;
        }
    }

#if !defined(BENCHMARK)
    cout << "Done ! Vent lines overlap at " << overlappingVentCoordinateCount << " points." << endl;
#endif // !BENCHMARK

    return EErrorCode::Success;
}

EErrorCode CChallenge_5::CleanUp_SecondPart()
{
    m_inputLines.clear();
    m_ventsLocations.clear();
    return EErrorCode::Success;
}
