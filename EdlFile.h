#ifndef EDLFILE_H
#define EDLFILE_H

class EdlFile : public QTextStream
{
  // Constructor
public:
  // *\brief  EdlFile text stream costructor
  // *\param device  -  pointer to QFile object

  EdlFile(QIODevice* device, QPlainTextEdit* plainTextEdit) : QTextStream(device) 
  {
    m_bIsSameSong = false;
    m_strSongName = "";
    m_strStartTime = "";
    m_strEndTime = "";
    m_pTextEdit = plainTextEdit;
  };

  void parseEdlFile();
private:
  void writeTitle(const QString& strLine);
  void writeContent(const QString& strLine);

  bool            m_bIsSameSong;
  QString         m_strSongName;
  QString         m_strStartTime;
  QString         m_strEndTime;
  QPlainTextEdit* m_pTextEdit;
};

#endif //EDLFILE_H
