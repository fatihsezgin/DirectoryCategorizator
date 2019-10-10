#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QLineEdit>
#include <QFileInfoList>
#include <QList>
#include <QMessageBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_selectDirectory_clicked();

    void on_pushBCategorize_clicked();

    void on_selectTargetButton_clicked();

    bool isCategorized(QString path );

private:
    Ui::MainWindow *ui;
    QLineEdit *lineEditSelectedDir;
    QLineEdit *lEditTarget;
    QDir directory;
    QDir targetDirectory;

};
#endif // MAINWINDOW_H
