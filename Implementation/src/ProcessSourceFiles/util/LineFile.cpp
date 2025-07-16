#include "LineFile.h"

#include <string>

#include "../../Logger/Log.h"

LineFile::LineFile() : m_line(0), m_col(0), m_endLine(0), m_endCol(0)
{
    Logger::getInstance().log(getLineFileAsString() + " with default values.");
}

LineFile::LineFile(int line, int col, int endLine, int endCol)
    : m_line(line), m_col(col), m_endLine(endLine), m_endCol(endCol)
{
    // TODO: Add validation for line and column numbers ( no negative numbers )
    Logger::getInstance().log(getLineFileAsString());
}

int LineFile::getLine() const
{
    return m_line;
}
int LineFile::getCol() const
{
    return m_col;
}
int LineFile::getEndLine() const
{
    return m_endLine;
}
int LineFile::getEndCol() const
{
    return m_endCol;
}

void LineFile::setLine(int line)
{
    m_line = line;
}
void LineFile::setCol(int col)
{
    m_col = col;
}
void LineFile::setEndLine(int endLine)
{
    m_endLine = endLine;
}
void LineFile::setEndCol(int endCol)
{
    m_endCol = endCol;
}

std::string LineFile::getLineFileAsString() const
{
    return "[LineFile] Line: " + std::to_string(m_line) + ", Col: " + std::to_string(m_col) +
           ", End Line: " + std::to_string(m_endLine) + ", End Col: " + std::to_string(m_endCol);
}