#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "des.h"
#include "rc4.h"
#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QThread>
#include "thread1.h"
#include <memory>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_rle_clicked()
{
    if(ui->radioButton->isChecked())
    {
        switch(ui->comboBox->currentIndex())
        {
            case 0:des_algorithm('D'); break;
            case 1: rc4(); break;
            case 2: rle(); break;
            case 3: huffman(); break;

        }

    }
    if(ui->radioButton_2->isChecked())
    {
        switch(ui->comboBox->currentIndex())
        {
            case 0:des_algorithm('d'); break;
            case 1: rc4_decoding(); break;
            case 2: rle_unarchiver(); break;
            case 3: huffman_unarchiver(); break;

        }
    }
}

void MainWindow::rle()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл для архівування"), "C:");
    if(fName!=NULL)
    {
       showProgressLine();
       MyThread  *thread = new MyThread('R',fName,"");
       connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
       thread->start();
    }

}
void MainWindow::rle_unarchiver()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл для розархівування"), "C:",tr("Archive (*.arc)"));
    if(fName!=NULL)
    {
        showProgressLine();
        MyThread  *thread = new MyThread('r',fName,"");
       connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
       thread->start();
    }

}

void MainWindow::huffman()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл для архівування"), "C:");
    if(fName!=NULL)
    {
        showProgressLine();
        MyThread  *thread = new MyThread('H',fName,"");
        connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
        thread->start();
    }
}

void MainWindow::huffman_unarchiver()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл для розархівування"), "C:",tr("Archive (*.arc)"));
    if(fName!=NULL)
    {
        showProgressLine();
        MyThread *thread= new MyThread('h',fName,"");
        connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
        thread->start();
    }
}

void MainWindow::rc4()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл"), "C:");

    if(fName!=NULL)
    {
       QString key = QInputDialog::getText( 0,"Input key", "Введіть ключ:",QLineEdit::Normal);
       if(key!=NULL)
       if(key.size()>=4 && key.size()<257)
       {
          showProgressLine();
          MyThread *thread= new MyThread('C',fName,key);
          connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
          thread->start();
       }
       else
       {
          QMessageBox::information(this,"Попередження","Неправильна довжина ключа");
       }
    }
}

void MainWindow::rc4_decoding()
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл"), "C:",tr("Encryption (*.enc)"));

      if(fName!=NULL)
      {
          QString key = QInputDialog::getText( 0,"Input key", "Введіть ключ:",QLineEdit::Normal);
          if(key!=NULL)
          if(key.size()>=4 && key.size()<257)
          {
              showProgressLine();
              MyThread *thread= new MyThread('c',fName,key);
              connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
              thread->start();
          }
          else
          {
              QMessageBox::information(this,"Попередження","Неправильна довжина ключа");
          }
      }

}



void MainWindow::des_algorithm(char f)
{
    QString fName = QFileDialog::getOpenFileName(this,tr("Оберіть файл"), "C:");

    if(fName!=NULL)
    {
        QString key = QInputDialog::getText( 0,"Input key", "Введіть ключ з 7 символів:",QLineEdit::Normal);
        if(key!=NULL)
        if(key.size()==7)
        {
            showProgressLine();
            MyThread * thread= new MyThread(f,fName,key);
            connect(thread, SIGNAL(send(bool)), this, SLOT(update(bool)));
            thread->start();
        }
        else
        {
            QMessageBox::information(this,"Попередження","Ключ повинен складатися з 7 символів");
        }
    }

}

 void MainWindow::showProgressLine()
 {
     ui->statusBar->showMessage("Зачекайте");
     ui->progressBar->setVisible(true);
     ui->progressBar->setMaximum(0);
     ui->progressBar->setMinimum(0);
 }
void MainWindow::update (bool i)
{
    if(i==1)
    {
        ui->statusBar->clearMessage();
        ui->progressBar->setMaximum(100);
        ui->progressBar->setValue(100);
        ui->progressBar->setVisible(false);
    }
}








void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==0 || index==1 )
    {
        ui->radioButton->setText("Зашифрувати");
        ui->radioButton_2->setText("Розшифрувати");
    }
    else
    {
        ui->radioButton->setText("Архівувати");
        ui->radioButton_2->setText("Розархівувати");
    }

}
