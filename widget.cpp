#include "widget.h"
#include "ui_widget.h"
#include <QDoubleValidator>
#include <QStorageInfo>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <string>
#include <sys/types.h>
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
bool rand1 = false;
bool full = false;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)

{
    ui->setupUi(this);
    this->setWindowTitle("Генератор плейлиста");

    QDoubleValidator *validator = new  QDoubleValidator(this);
    ui->progressBar->setVisible(false);
    ui->lineEdit->setValidator(validator);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

Widget::~Widget()
{
    delete ui;
}


long printRootDriveInfo(QDir(filed)) {
  // QStorageInfo storage = QStorageInfo::root();
QStorageInfo storage(filed);
   qDebug() << storage.rootPath();
   if (storage.isReadOnly())
       qDebug() << "isReadOnly:" << storage.isReadOnly();

   qDebug() << "name:" << storage.name();
   qDebug() << "filesystem type:" << storage.fileSystemType();
   qDebug() << "size:" << storage.bytesTotal()/1024/1024 << "MB";
   qDebug() << "free space:" << storage.bytesAvailable()/1024/1024 << "MB";
return storage.bytesAvailable();
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
    ui->label_5->setText("");
    unsigned long long size1 = printRootDriveInfo(fileName2);
    int  file1=0;
    QString x= ui->lineEdit->text();
    if (x==".")
    {
        ui->label_3->setText("введите число для копирования\n");
        return;
    }
    bool ok = false;
    bool ok1 = true;
    int numder1=0;
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
          if (!ok && !full){
              ui->label_3->setText("введите число для копирования\n");
              return;
          }
          unsigned long long siz =0;
          fileName1.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);   ///устанавливаем фильтр выводимых файлов/папок (см ниже)
          fileName1.setSorting(QDir::Size | QDir::Reversed);   //устанавливаем сортировку "от меньшего к большему"
          QFileInfoList list = fileName1.entryInfoList(nameFilter,QDir::Files); //получаем список файлов директории
          std::cout << "     Bytes Filename" << std::endl;   //выводим заголовок
          /* в цикле выводим сведения о файлах */
          for (int i = 0; i < list.size(); ++i) {
              QFileInfo fileInfo = list.at(i);
             // std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));   //выводим в формате "размер имя"
            //  std::cout << std::endl;  //переводим строку
          }


          fileName2.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);   ///устанавливаем фильтр выводимых файлов/папок (см ниже)
          fileName2.setSorting(QDir::Size | QDir::Reversed);   //устанавливаем сортировку "от меньшего к большему"
          QFileInfoList list1 = fileName2.entryInfoList(nameFilter,QDir::Files);
          if(list1.size()>0)
          {
              if(list1.size()<list.size()){
          for (int i = 0; i < list1.size(); ++i) {
                QFileInfo fileInfo = list.at(i);
                  QFileInfo fileInfo1 = list1.at(i);
               if (fileInfo.fileName()==fileInfo1.fileName())
              {
                      ui->label_3->setText("Выявлен дубликат, копирование приостановлено\n");
                      return;
                  }}}
          else {
                  for (int i = 0; i < list.size(); ++i) {
                QFileInfo fileInfo = list.at(i);
                  QFileInfo fileInfo1 = list1.at(i);
                      if (list.at(i)==list1.at(i))
                      {
                              ui->label_3->setText("Выявлен дубликат, копирование приостановлено\n");
                              return;
                          }
          }
          }
          }


std::cout << std::endl;

                if (!rand1){
                  for (int i = list.size() - 1; i >= 1; i--)
                  {
                      srand ( time(NULL) );
                      int j = rand() % i+1 ;

                     QFileInfo  tmp = list[j];
                      list[j] = list[i];
                      list[i] = tmp;
                  }}


                  QString files_list;
                  if (file1 > list.size()) {
                      file1 = list.size();
                  }


                  for (int i = 0; i < file1; i++) {
                      QFileInfo fileInfo = list.at(i);
                      siz = siz + fileInfo.size();
                      files_list += list[i].absoluteFilePath() + "\n";
                  }

                  if (full){
                   int  i=0;
                   unsigned long long sizz=0;
                   bool flags=false;
                   siz=0;
                    while((siz<size1))
                    {
                        if(siz<size1){
                       QFileInfo fileInfo = list.at(i);
                        siz = siz + fileInfo.size();
                      std::cout <<fileInfo.size() <<std::endl;
                      std::cout <<siz <<std::endl;
                      std::cout <<size1 <<std::endl;
                      std::cout <<list.size() <<std::endl;
                      std::cout << i;
                       std::cout << std::endl;
                        i=i+1;
                      if (i == list.size())
                      {
                         sizz=siz;
                        siz=size1+10;
                        flags=true;
                        std::cout <<siz <<std::endl;
                      }

                    }}
                    if (flags){
                siz=sizz;
                    }
                    i=i-1;
                    QFileInfo fileInfo = list.at(i);
                     siz = siz - fileInfo.size();
                    file1=i;

                  }
                  if (file1 > list.size()) {
                      file1 = list.size();
                  }
                  std::cout <<siz <<std::endl;
                  std::cout <<size1 <<std::endl;
                 if (siz>size1)
           {
              ui->label_3->setText("размер плейлиста больше свободного места");

           }
                 if (file1 == 0) {
                     ui->label_3->setText("Нет файлов для копирования.\n");
                     return;
                 }
     else {
      ui->progressBar->setVisible(true);
      ui->label_3->setText("копирование началось \n");
      int j=0;
    if (flag==false){
        for (int i = 0; i < file1; i++) {
            ui->progressBar->setValue( ((double) i/ (double) file1)*100 );

        if (!QFile::copy(list[i].absoluteFilePath(), fileName2.absolutePath() + '/' + list[i].fileName())) {
            std::cerr << "Couldn't copy file!!!\n";
            if (i>0 && i<list.size())
            {
                ui->label_3->setText("Выявлен дубликат,скопированных файлов:\n");
               ui->label_5->setText( QString::number(numder1));
                return;
            }
            ui->label_3->setText("Не удалось скопировать файл!!!\n");
            ok1=false;
            break;
        }
            numder1=i+1;
        }
    }
    if (flag==true)
    {
        for (int i = 0; i < file1; i++)
        {
            ui->progressBar->setValue( ((double) i/ (double) file1)*100 );
            QString name1=QString::number(i+1);
            if (!QFile::copy(list[i].absoluteFilePath(), fileName2.absolutePath() + '/' +name1+" ."+ list[i].fileName())) {
                std::cerr << "Couldn't copy file!!!\n";
                if (i>0 && i<list.size())
                {
                    ui->label_3->setText("Выявлен дубликат, копирование приостановлено\n");
                    return;
                }
                ok1=false;
                ui->label_3->setText("Не удалось скопировать файл!!!\n");
                break;
            }
            numder1=i+1;
        }
    }
    if (ok1){
    ui->progressBar->setValue(100);
    ui->label_3->setText("копирование завершено, файлов скопировано: \n");
    ui->label_5->setText( QString::number(numder1));
    }}
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




void Widget::on_checkBox_2_clicked(bool checked)
{
    if (checked==false)
    {
        rand1 = false;
    }
    if (checked==true)
    {
        rand1 = true;
    }
}

void Widget::on_checkBox_3_clicked(bool checked)
{
    if (checked==false)
    {
        full = false;
        ui->lineEdit->setEnabled(true);
    }
    if (checked==true)
    {
        full = true;
        ui->lineEdit->setEnabled(false);
    }
}
