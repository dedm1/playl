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
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

QDir fileName1;
QDir fileName2;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
     fileName1 = QFileDialog::getExistingDirectory(this, tr("откуда"), "");

     ui->label->setText(fileName1.dirName());
}


void Widget::on_pushButton_2_clicked()
{
    fileName2 = QFileDialog::getExistingDirectory(this, tr("куда"), "");
   // QString x=fileName2;
   ui->label_2->setText(fileName2.dirName());
}

void perzapis(QFileInfoList list )
{

}
void Widget::on_pushButton_3_clicked()
{
    int  file1;
    QString x= ui->lineEdit->text();
    bool ok = false;
      file1 = x.toInt(&ok, 10);
      if (!ok) {
          ui->label_3->setText("Couldn't get a number from input!!!\n");
          return;
      }
     //консольное приложение
          QStringList nameFilter;
          nameFilter << "*.h" << "*.o";
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
    ui->label_3->setText(files_list);
    for (int i = 0; i < file1; i++) {
        if (!QFile::copy(list[i].absoluteFilePath(), fileName2.absolutePath() + '/' + list[i].fileName())) {
            std::cerr << "Couldn't copy file!!!\n";
            ui->label_3->setText("Couldn't copy file!!!\n");
            break;
        }
    }
}
