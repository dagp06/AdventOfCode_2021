#pragma once

#include "Common/Challenge.h"

#include <set>

using namespace std;

class CChallenge_13 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    class Dot
    {
    public:
        Dot(int _x, int _y) : m_X(_x), m_Y(_y) {}

        friend bool operator< (const Dot& _lhs, const Dot& _rhs)
        {
            return _lhs.m_X < _rhs.m_X || (_lhs.m_X == _rhs.m_X && _lhs.m_Y < _rhs.m_Y);
        }

        const int& X() const { return m_X; }
        const int& Y() const { return m_Y; }
    private:
        int m_X = 0;
        int m_Y = 0;
    };

    class FoldCommand
    {
    public:
        FoldCommand(bool _isAlongX, int _pos) : m_isAlongX(_isAlongX), m_pos(_pos) {}

        const bool& IsAlongX() const { return m_isAlongX; }
        const int& GetPos() const { return m_pos; }

    private:
        bool m_isAlongX = false;
        int m_pos = 0;
    };

    set<Dot> m_dots;
    vector<FoldCommand> m_foldCommands;
};
