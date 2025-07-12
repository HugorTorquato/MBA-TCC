#pragma once

#include <string>

class LineFile
{
   public:
    LineFile();
    LineFile(int line, int col, int endLine, int endCol);

    int getLine() const;
    int getCol() const;
    int getEndLine() const;
    int getEndCol() const;

    void setLine(int line);
    void setCol(int col);
    void setEndLine(int endLine);
    void setEndCol(int endCol);

    std::string getLineFileAsString() const;

   private:
    int m_line;
    int m_col;
    int m_endLine;
    int m_endCol;
};