#include "Challenge_13.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
string const CChallenge_13::sm_inputFilePath = "Inputs/Input_Challenge_13.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_FirstPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Read dots positions
    int i = 0;
    while (!lines[i].empty())
    {
        vector<string> args;
        FileHelper::SplitLine(lines[i], ",", args);
        m_dots.insert(Dot(stoi(args[0]), stoi(args[1])));

        ++i;
    }

    // Read first folding instruction
    vector<string> args;
    FileHelper::SplitLine(lines[++i], "=", args);
    m_foldCommands.push_back(FoldCommand(args[0].back() == 'x', stoi(args[1])));

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::Run_FirstPart()
{
    for (const FoldCommand& command : m_foldCommands)
    {
        int pos = command.GetPos();
        for (set<Dot>::iterator it = m_dots.begin(); it != m_dots.end();)
        {
            const Dot& dot = *it;
            if (command.IsAlongX())
            {
                if (dot.X() >= pos)
                {
                    if (dot.X() > pos)
                    {
                        // Add new mirror dot
                        m_dots.insert(Dot(pos - (dot.X() - pos), dot.Y()));
                    }

                    // Remove current dot
                    m_dots.erase(it++);
                    continue;
                }
            }
            else
            {
                if (dot.Y() >= pos)
                {
                    if (dot.Y() > pos)
                    {
                        // Add new mirror dot
                        m_dots.insert(Dot(dot.X(), (pos - (dot.Y() - pos))));
                    }

                    // Remove current dot
                    m_dots.erase(it++);
                    continue;
                }
            }

            ++it;
        }
    }

#if !defined(BENCHMARK)
    cout << "Done ! There are " << m_dots.size() << " dots visible after the first folding instruction." << endl;
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_FirstPart()
{
    m_dots.clear();
    m_foldCommands.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_SecondPart()
{
    vector<string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    // Read dots positions
    int i = 0;
    while (!lines[i].empty())
    {
        vector<string> args;
        FileHelper::SplitLine(lines[i], ",", args);
        m_dots.insert(Dot(stoi(args[0]), stoi(args[1])));

        ++i;
    }

    // Read folding instructions
    ++i;
    m_foldCommands.reserve(lines.size() - i);
    for (; i < lines.size(); ++i)
    {
        vector<string> args;
        FileHelper::SplitLine(lines[i], "=", args);
        m_foldCommands.push_back(FoldCommand(args[0].back() == 'x', stoi(args[1])));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::Run_SecondPart()
{
    for (const FoldCommand& command : m_foldCommands)
    {
        int pos = command.GetPos();
        for (set<Dot>::iterator it = m_dots.begin(); it != m_dots.end();)
        {
            const Dot& dot = *it;
            if (command.IsAlongX())
            {
                if (dot.X() >= pos)
                {
                    if (dot.X() > pos)
                    {
                        // Add new mirror dot
                        m_dots.insert(Dot(pos - (dot.X() - pos), dot.Y()));
                    }

                    // Remove current dot
                    m_dots.erase(it++);
                    continue;
                }
            }
            else
            {
                if (dot.Y() >= pos)
                {
                    if (dot.Y() > pos)
                    {
                        // Add new mirror dot
                        m_dots.insert(Dot(dot.X(), (pos - (dot.Y() - pos))));
                    }

                    // Remove current dot
                    m_dots.erase(it++);
                    continue;
                }
            }

            ++it;
        }
    }

    // Find grid size
    int maxX = 0;
    int maxY = 0;
    for (const Dot& dot : m_dots)
    {
        maxX = max(dot.X() + 1, maxX);
        maxY = max(dot.Y() + 1, maxY);
    }

#if !defined(BENCHMARK)
    // Display dots
    vector<vector<char>> m_dotsDisplay(maxX, vector<char>(maxY, '.'));
    for (const Dot& dot : m_dots)
    {
        m_dotsDisplay[dot.X()][dot.Y()] = '#';
    }

    for (const vector<char>& row : m_dotsDisplay)
    {
        for (const char& character : row)
        {
            cout << character;
        }
        cout << endl;
    }
#endif

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_SecondPart()
{
    m_dots.clear();
    m_foldCommands.clear();
    return EErrorCode::Success;
}
