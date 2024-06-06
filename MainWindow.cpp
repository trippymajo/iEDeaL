#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  QWidget* mainWidget = new QWidget(this);
  setCentralWidget(mainWidget);

  QVBoxLayout* mainLay = new QVBoxLayout;
  mainWidget->setLayout(mainLay);

  menuBar = new QMenuBar;

  textEdit = new QPlainTextEdit;

  mainLay->addWidget(menuBar);
  mainLay->addWidget(textEdit);
}

MainWindow::~MainWindow()
{
}
