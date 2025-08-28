#pragma once

#include <string>

class LineFile
{
   public:
    LineFile();
    LineFile(int line, int col, int endLine, int endCol);
    LineFile(int line, int col, int endLine, int endCol, const std::string& fileName);

    int getLine() const;
    int getCol() const;
    int getEndLine() const;
    int getEndCol() const;
    std::string getFileName() const;

    void setLine(int line);
    void setCol(int col);
    void setEndLine(int endLine);
    void setEndCol(int endCol);
    void setFileName(const std::string& fileName);

    std::string getLineFileAsString() const;

   private:
    std::string m_fileName;  // Optional: if you want to track the file name
    // Line and column numbers
    int m_line;
    int m_col;
    int m_endLine;
    int m_endCol;
};