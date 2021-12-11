#pragma once

#include "Common/Challenge.h"
#include <map>

using namespace std;

class CChallenge_5 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    struct Coordinate
    {
        Coordinate() : X(0), Y(0) {}
        Coordinate(int _x, int _y) : X(_x), Y(_y) {}

        int X = 0;
        int Y = 0;

        friend bool operator< (const Coordinate& c1, const Coordinate& c2)
        {
            return c1.X < c2.X || (c1.X == c2.X && c1.Y < c2.Y);
        }
    };

    vector<string> m_inputLines;
    map<Coordinate, int> m_ventsLocations;
};
