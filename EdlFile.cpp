#include "stdafx.h"
#include "EdlFile.h"

#include <QVector>

#define REGEXP_WHITESPACES "\\s+"

static const QString s_strPrefixSongName = "* FROM CLIP NAME:";

const static QString s_strPatternsEdl [] =
{
  "^TITLE:.*$",
  "^\\d+\\s+\\w+.*$"
  //Add more patterns if you want to...
};

static int s_iPattensEdlSize = sizeof(s_strPatternsEdl) / sizeof(s_strPatternsEdl[0]);

/// @brief  Converts time from HH:MM:SS:mm to MM::SS if possible
/// @param  str  -  string to copy
/// @return  QString  -  Copy of the passed parameter in right format
QString makeNiceTime(const QString& str)
{
  QString retVal = str;
  retVal.remove(8, 3);
  if (retVal.startsWith("00:"))
    retVal.remove(0, 3);
  return retVal;
}

void EdlFile::writeContent(const QString& strLine)
{
  //Read second line of the block
  QString strSongName;
  if (!QTextStream::atEnd())
  {
    strSongName = QTextStream::readLine();

    //Ingore timelines with no audio line
    if (strSongName.isEmpty()) 
      return;

    //Ignore names without file format, because it is not songs
    if (!strSongName.contains("."))
      return;

    strSongName = strSongName.mid(s_strPrefixSongName.length());
  }

  //Read first line, set text data
  QStringList strList = strLine.split(QRegularExpression(REGEXP_WHITESPACES));
  if (strSongName == m_strSongName)
    m_strEndTime = makeNiceTime(strList[7]);
  else
  {
    m_pTextEdit->appendPlainText(QString("%1 - %2  %3").arg(m_strStartTime).arg(m_strEndTime).arg(m_strSongName));

    m_strStartTime = makeNiceTime(strList[6]);
    m_strEndTime = makeNiceTime(strList[7]);
    m_strSongName = strSongName;
  }
}

void EdlFile::writeTitle(const QString &strLine)
{
  m_pTextEdit->appendPlainText(strLine);
}

void EdlFile::parseEdlFile()
{
  while (!QTextStream::atEnd())
  {
    QString strLine = QTextStream::readLine();

    if (strLine.isEmpty())
      continue;
    
    //Go through patterns (This was make if there will be futher regexps for parsing)
    for (int i = 0; i < s_iPattensEdlSize; ++i)
    {
      if (strLine.contains(QRegularExpression(s_strPatternsEdl[i])))
        i == 1 ? writeContent(strLine) : writeTitle(strLine);
    }
  }
}