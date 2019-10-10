#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectDirectory_clicked()
{

    directory.setPath(QFileDialog::getExistingDirectory(this,tr("Select Directory")));
    ui->lineEditSelectedDir->setText(directory.path());
    //qDebug() <<  directory.path();

}

void MainWindow::on_selectTargetButton_clicked()
{
    targetDirectory.setPath(QFileDialog::getExistingDirectory(this,tr("Select Target Directory")));
    ui->lEditTarget->setText(targetDirectory.path());

}

bool MainWindow::isCategorized(QString path)
{
    int count = 0 ;
    QDir dir(path);
    if(dir.mkdir("PDFs")){//mkdir returns false if exists
        qDebug() << "PDFs created.";
        count++;
    }
    if (dir.mkdir("ZIPs")){
        qDebug() << "ZIPs created.";
        count++;
    }

    if(count ==0 || count ==1 ){
        return true;
    }else
        return false;

}

void MainWindow::on_pushBCategorize_clicked()
{
    if((ui->lineEditSelectedDir->text().isEmpty()) || (ui->lEditTarget->text().isEmpty())){
        QMessageBox::information(this,tr("Directories must be given"),
                                 tr("Please enter all the informations"));
        return;
    }

    qDebug() << targetDirectory.path()<< " This is the targetDirectory";
    if(isCategorized(targetDirectory.path())){
        qDebug() << "True döndüü";
        int count=0;

        QFileInfoList files = directory.entryInfoList();

        for (int index = 0; index < files.size();index++) {
            const QFileInfo& info = files.at(index);
            qDebug() << info.suffix();
            if(info.fileName() == "." || info.fileName() == ".."){
                continue;
            }

            if(info.suffix()=="pdf"){

                //qDebug() << info.filePath() << targetDirectory.path()+"/PDFs"+"/"+info.fileName();
                if(QFile::copy(info.filePath(),targetDirectory.path()+"/PDFs" +"/"+info.fileName())){
                    count++;
                    qDebug() << "Successfull" ;
                }
            }else if(info.suffix() == "zip" || info .suffix() == "gz"){
                if(QFile::copy(info.filePath(),targetDirectory.path()+"/ZIPs" +"/"+info.fileName())){
                    count++;
                    qDebug() << "Successfull" ;
                }

            }
        }
        QMessageBox::information(this,tr("Successfull"),
                                 QString::number(count)+"files succesfully moved");
    }




}




