#ifndef MAINWINDOW_H
#define MAINWINDOW_H

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QMenu;
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {};

private:
  bool                  m_bDocChanged;
  //Menu Bar
  QMenu*                m_pFileMenu;
  QAction*              m_pActFileNew;
  //QAction*              m_pActFileOpen; //Feature fileOpen
  //QAction*              m_pActFileSave; // Feature fileSave
  QAction*              m_pActFileSaveAs;
  QAction*              m_pActFileExportEDL;
  QAction*              m_pActFileRecentFiles; //TODO
  QAction*              m_pActFileExit;
  //TextEdit
  QPlainTextEdit*       m_pTextEdit;

  void createActions();
  void makeMenuBar();

public:
  void setDocChanged(const bool& bVal);

signals:
  void docChanged(const bool& bDocChanged);

private slots:
  void newFile();
  //void saveFile(); // Feature fileSave
  void saveAsFile();
  //void openFile(); // Feature fileOpen
  void exportEDL();
  void exitProg();
  void onDocChanged(const bool& bVal);
};
#endif //MAINWINDOW_H