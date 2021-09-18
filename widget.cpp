#include "widget.h"
#include "ui_widget.h"
#include <QDoubleValidator>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <QLabel>
#include <random>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

/*function... might want it in some class?*/


QDir fileName1;
QDir fileName2;
bool flag = false;
bool flag1= false;
bool flag2 = false;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    flag1= true;
     fileName1 = QFileDialog::getExistingDirectory(this, tr("откуда"), "");
     ui->label->setText(fileName1.dirName());
}


void Widget::on_pushButton_2_clicked()
{
    flag2= true;
    fileName2 = QFileDialog::getExistingDirectory(this, tr("куда"), "");
   ui->label_2->setText(fileName2.dirName());
}

void Widget::on_pushButton_3_clicked()
{
    int  file1=0;
    QString x= ui->lineEdit->text();
    bool ok = false;
    bool ok1 = true;
    int numder=0;
      file1 = x.toInt(&ok, 10);
          QStringList nameFilter;
          nameFilter << "*.mp3" ;
          if (!flag1 )
          {
            ui->label_3->setText("нажмите на кнопку выбрать папку\n");
            return;
          }
          if (!flag2)
          {
            ui->label_3->setText("нажмите на кнопку скопировать в\n");
            return;
          }
          if (!ok) {
              ui->label_3->setText("введите число для копирования\n");
              return;
          }
          fileName1.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);   ///устанавливаем фильтр выводимых файлов/папок (см ниже)
          fileName1.setSorting(QDir::Size | QDir::Reversed);   //устанавливаем сортировку "от меньшего к большему"
          QFileInfoList list = fileName1.entryInfoList(nameFilter,QDir::Files); //получаем список файлов директории
          std::cout << "     Bytes Filename" << std::endl;   //выводим заголовок
          /* в цикле выводим сведения о файлах */
          for (int i = 0; i < list.size(); ++i) {
              QFileInfo fileInfo = list.at(i);
              std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));   //выводим в формате "размер имя"
              std::cout << std::endl;  //переводим строку
          }
std::cout << std::endl;
                  for (int i = list.size() - 1; i >= 1; i--)
                  {
                      srand ( time(NULL) );
                      int j = rand() % i+1 ;

                     QFileInfo  tmp = list[j];
                      list[j] = list[i];
                      list[i] = tmp;
                  }
                  QString files_list;
                  if (file1 > list.size()) {
                      file1 = list.size();
                  }
                  for (int i = 0; i < file1; i++) {
                      files_list += list[i].absoluteFilePath() + "\n";
                  }
    //ui->label_3->setText(files_list);
      ui->progressBar->setVisible(true);
      ui->label_3->setText("копирование началось \n");
      //ui->progressBar->setValue(15);
    if (flag==false){
        for (int i = 0; i < file1; i++) {
            ui->progressBar->setValue( ((double) i/ (double) file1)*100 );
        if (!QFile::copy(list[i].absoluteFilePath(), fileName2.absolutePath() + '/' + list[i].fileName())) {
            std::cerr << "Couldn't copy file!!!\n";
            ui->label_3->setText("Не удалось скопировать файл!!!\n");
            ok1=false;
            break;
        }
            numder=i;
        }
    }
    if (flag==true)
    {
        for (int i = 0; i < file1; i++) {
            ui->progressBar->setValue( ((double) i/ (double) file1)*100 );
            QString name1=QString::number(i);
            if (!QFile::copy(list[i].absoluteFilePath(), fileName2.absolutePath() + '/' +name1+ list[i].fileName())) {
                std::cerr << "Couldn't copy file!!!\n";
                ok1=false;
                ui->label_3->setText("Не удалось скопировать файл!!!\n");
                break;
            }
            numder=i;
        }
    }
    if (ok1){    ui->progressBar->setValue(100);
    ui->label_3->setText("копирование завершено, файлов скопиравнно: \n");
    ui->label_5->setText( QString::number(numder));
    }
}




void Widget::on_checkBox_clicked(bool checked)
{
    if (checked==false)
    {
        flag = false;
    }
    if (checked==true)
    {
        flag = true;
    }
}
