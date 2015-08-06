#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toxml.h"
#include "tocsv.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//knoxville leads browse
void MainWindow::on_pushButton_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("CSV files (*.csv)"));
    ui->lineEdit->setText(fileName);
}

//asheville leads browse
void MainWindow::on_pushButton_2_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("CSV files (*.csv)"));
    ui->lineEdit_2->setText(fileName);
}

//to xml save as
void MainWindow::on_pushButton_3_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/path/to/file/",tr("XML files (*.xml);;All files (*)"));
    ui->lineEdit_3->setText(fileName);
}

//ebureau out browse
void MainWindow::on_pushButton_4_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("XML files (*.xml)"));
    ui->lineEdit_4->setText(fileName);
}

//to csv save as
void MainWindow::on_pushButton_5_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/path/to/file/",tr("CSV files (*.csv);;All files(*)"));
    ui->lineEdit_5->setText(fileName);
}

//to xml convert
void MainWindow::on_pushButton_6_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");

    //send to toxml_main
    try
    {
        toxml_main(ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString(), ui->lineEdit_3->text().toStdString());
        ui->label_9->setText("Conversion success!");
    }
    catch (const invalid_argument &e)
    {
        ui->label_9->setText(e.what());
    }

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}

//to csv convert
void MainWindow::on_pushButton_7_clicked()
{
    ui->label_9->setText("");
    ui->label_10->setText("");

    //send to tocsv_main
    try
    {
        tocsv_main(ui->lineEdit_4->text().toStdString(), ui->lineEdit_5->text().toStdString());
        ui->label_10->setText("Conversion success!");
    }
    catch (const invalid_argument &e)
    {
        ui->label_10->setText(e.what());
    }

    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
}
