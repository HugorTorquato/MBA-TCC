#include "LineFile.h"

#include <string>

#include "../../Logger/Log.h"

LineFile::LineFile(int line, int col, int endLine, int endCol)
    : m_line(line), m_col(col), m_endLine(endLine), m_endCol(endCol)
{
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

std::string LineFile::logLineFile() const
{
    return "[LineFile] Line: " + std::to_string(m_line) + ", Col: " + std::to_string(m_col) +
           ", End Line: " + std::to_string(m_endLine) + ", End Col: " + std::to_string(m_endCol);
}