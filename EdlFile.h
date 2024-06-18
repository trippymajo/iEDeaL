#ifndef EDLFILE_H
#define EDLFILE_H

class EdlFile : public QTextStream
{
  // Constructor
public:

  /// @brief  EdlFile text stream costructor
  /// @param  [OUT] device  -  poiner to file for read
  /// @param  [OUT] plainTextEdit  -  pointer to plain text edit widget
  EdlFile(QIODevice* device, QPlainTextEdit* plainTextEdit) : QTextStream(device) 
  {
    m_bIsSameSong = false;
    m_strSongName = "";
    m_strStartTime = "";
    m_strEndTime = "";
    m_pTextEdit = plainTextEdit;
  };

  /// @brief reads line from stream and parses it
  void parseEdlFile();


private:
  /// @brief  Writes string containing TITLE: infromation to PlainTextEdit
  /// @param  strLine  -  line to wrtite data from
  void writeTitle(const QString& strLine);

  /// @brief  Writes track's times and names from string line & TextStream
  /// @param  strLine  -  line to wrtite data from
  void writeContent(const QString& strLine);

  bool            m_bIsSameSong;
  QString         m_strSongName;
  QString         m_strStartTime;
  QString         m_strEndTime;
  QPlainTextEdit* m_pTextEdit;
};

#endif //EDLFILE_H
