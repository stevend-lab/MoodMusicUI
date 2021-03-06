#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QtCore>

#include <QPixmap>

#include <QtDebug>

#include <QString>

#include <QTimer>

#include <QProcess>

#include <string>

#include <Windows.h>

#include <stdlib.h>

#include <stdio.h>

#include <QFuture>

#include <winbase.h>

#include <processthreadsapi.h>

#include <QTextStream>

#include <QFile>

#include <QCloseEvent>

// thread that runs python application
class MyThread: public QThread {
  void run() override {

    WinExec("python C:\\Users\\Steven\\MoodMusic", SW_HIDE);
  }
};

// main window
MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {

  ui -> setupUi(this);
  this -> setStyleSheet("background-color: black;");

  int w = ui -> label_pic -> width();
  int h = ui -> label_pic -> height();

  QPixmap pix("C:/Users/Steven/Documents/MoodMusicUI/images/brain.png");
  ui -> label_pic -> setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

  ui -> progressBar -> setValue(ui -> horizontalSlider -> value());
  connect(ui -> horizontalSlider, SIGNAL(valueChanged(int)), ui -> progressBar, SLOT(setValue(int)));

  MyThread * thread = new MyThread;
  thread -> start();

}

MainWindow::~MainWindow() {
  qInfo() << "fired off";
  WinExec("TASKKILL /F /IM Python.exe 2>NULL", SW_HIDE);
  WinExec("TASKKILL /F /IM cmd.exe 2>NULL", SW_HIDE);
  delete ui;
}
