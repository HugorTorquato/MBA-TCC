#pragma once

#include <string>

class LineFile
{
   public:
    LineFile(int line, int col, int endLine, int endCol);

    int getLine() const;
    int getCol() const;
    int getEndLine() const;
    int getEndCol() const;

    std::string logLineFile() const;

   private:
    int m_line;
    int m_col;
    int m_endLine;
    int m_endCol;
};