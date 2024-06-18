#include "stdafx.h"
#include "MainWindow.h"
#include "EdlFile.h"

#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  m_bDocChanged = false; // init before creating Actions and slot signals

  QWidget* mainWidget = new QWidget(this);
  setCentralWidget(mainWidget);
  setWindowTitle("iEDeaL");

  QVBoxLayout* mainLay = new QVBoxLayout;
  mainWidget->setLayout(mainLay);


  QWidget* MenuBar = new QWidget;
  m_pTextEdit = new QPlainTextEdit;
  createActions();
  makeMenuBar();

  mainLay->addWidget(MenuBar);
  mainLay->addWidget(m_pTextEdit);
}

void MainWindow::newFile()
{
  if (m_bDocChanged)
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Save changes?"), tr("Do you want to save current document before new?"),
      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
      saveAsFile();
  }
  m_pTextEdit->clear();
  setWindowTitle("New Document");
}

void MainWindow::saveAsFile()
{
  QString strFileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Text Files (*.txt);;All files (*.*)"));
  if (!strFileName.isEmpty()) 
  {
    QFile file(strFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
      QTextStream streamOut (&file);
      streamOut << m_pTextEdit->toPlainText();
      setWindowTitle(file.fileName());
      m_bDocChanged = false;
      file.close();
    }
    else
      qInfo() << "Error: Unable to open file for writing.";
  }
}

void MainWindow::exportEDL()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("File to export from"), "", tr("Edit Decision Lists (*.edl);;All files (*.*)"));
    if (fileName.isEmpty())
    {
      QMessageBox::warning(this, tr("Error!"), tr("Exporting file name is empty!"));
      return;
    }

  QFile file(fileName);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    EdlFile edlFile(&file, m_pTextEdit);
    QFileInfo fileInfo(file);
    setWindowTitle(fileInfo.fileName());
    edlFile.parseEdlFile();
    file.close();
  }
  else
    qInfo() << "Error: Unable to open file for reading.";
}

void MainWindow::exitProg()
{
  if (m_bDocChanged)
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Exit iEDeal?"), tr("Do you want to save current document before quit?"),
      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
      saveAsFile();
  }
  QApplication::quit();
}

// Feature here or not? Will see in future ;-)
// Feature fileOpen
//void MainWindow::openFile()
//{
//  QString fileName = QFileDialog::getOpenFileName(this, tr("Open the file"));
//
//  if (fileName.isEmpty())
//  {
//    QMessageBox::warning(this, tr("Error!"), tr("File name is empty!"));
//    return;
//  }
//
//  QFile file(fileName);
//  if (!file.open(QIODevice::ReadOnly | QFile::Text)) 
//  {
//    QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
//    return;
//  }
//  setWindowTitle(fileName);
//  QTextStream in(&file);
//  QString text = in.readAll();
//  m_pTextEdit->setPlainText(text);
//  file.close();
//}

void MainWindow::setDocChanged(const bool& bVal)
{
  if (m_bDocChanged != bVal) 
  {
    m_bDocChanged = bVal;
    emit docChanged(bVal);
  }
}

void MainWindow::onDocChanged(const bool& bVal)
{
  QString strTitle = windowTitle();
  bVal ? strTitle.push_back('*') : strTitle.chop(1);
  setWindowTitle(strTitle);
}

/// <summary>
/// Creates actions for menu buttons
/// </summary>
void MainWindow::createActions()
{
  // File->New
  m_pActFileNew = new QAction(tr("&New"), this);
  m_pActFileNew->setShortcuts(QKeySequence::New);
  m_pActFileNew->setStatusTip(tr("Create a new file"));
  connect(m_pActFileNew, &QAction::triggered, this, &MainWindow::newFile);

  //m_pActFileSave = new QAction(tr("&Save"), this);
  //m_pActFileSave->setShortcuts(QKeySequence::Save);
  //m_pActFileSave->setStatusTip(tr("Save current file"));
  //connect(m_pActFileSave, &QAction::triggered, this, &MainWindow::saveFile);

  m_pActFileSaveAs = new QAction(tr("&SAve As"), this);
  m_pActFileSaveAs->setShortcuts(QKeySequence::SaveAs);
  m_pActFileSaveAs->setStatusTip(tr("Save current file as txt"));
  connect(m_pActFileSaveAs, &QAction::triggered, this, &MainWindow::saveAsFile);

  m_pActFileExportEDL = new QAction(tr("&Export"));
  m_pActFileExportEDL->setShortcut(QKeySequence("Ctrl+E"));
  m_pActFileExportEDL->setStatusTip(tr("Open a EDL file to export"));
  connect(m_pActFileExportEDL, &QAction::triggered, this, &MainWindow::exportEDL);

  m_pActFileExit = new QAction(tr("E&xit"), this);
  m_pActFileExit->setShortcuts(QKeySequence::Quit);
  m_pActFileExit->setStatusTip(tr("Exit program"));
  connect(m_pActFileExit, &QAction::triggered, this, &MainWindow::exitProg);

  connect(m_pTextEdit, &QPlainTextEdit::textChanged, [this]() 
    {
      setDocChanged(true);
    });

  connect(this, &MainWindow::docChanged, this, &MainWindow::onDocChanged);
}

/// <summary>
/// Adds menus & actions, draws menuBar. 
/// </summary>
void MainWindow::makeMenuBar()
{
  m_pFileMenu = menuBar()->addMenu(tr("&File"));
  m_pFileMenu->addAction(m_pActFileNew);
  //m_pFileMenu->addAction(m_pActFileSave);
  m_pFileMenu->addAction(m_pActFileSaveAs);
  m_pFileMenu->addAction(m_pActFileExportEDL);
  m_pFileMenu->addAction(m_pActFileExit);

}