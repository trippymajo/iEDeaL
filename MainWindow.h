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
    ~MainWindow();

private:
  //Menu Bar
  QMenu*                m_pFileMenu;
  QAction*              m_pActFileNew;
  //QAction*              m_pActFileOpen; //Feature fileOpen
  QAction*              m_pActFileSave;
  QAction*              m_pActFileSaveAs;
  QAction*              m_pActFileExportEDL;
  QAction*              m_pActFileRecentFiles; //TODO
  QAction*              m_pActFileExit;
  //
  QPlainTextEdit*       m_pTextEdit;

  void createActions();
  void makeMenuBar();

private slots:
  void newFile();
  void saveFile();
  void saveAsFile();
  //void openFile(); // Feature fileOpen
  void exportEDL();
  void exitProg();
};
#endif //MAINWINDOW_H