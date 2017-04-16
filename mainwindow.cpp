﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("FeaLizer 0.1beta");
    coeffs[0] = 0.1;
    coeffs[1] = 0.1;
    coeffs[2] = 0.1;
    coeffs[3] = 0.1;
    coeffs[4] = 0.1;
    coeffs[5] = 0.1;
    coeffs[6] = 0.1;
    coeffs[7] = 0.1;
    coeffs[8] = 0.1;
    coeffs[9] = 0.1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// decodes the file into memory
void MainWindow::on_openButton_clicked()
{
    QString currentFileName = QFileDialog::getOpenFileName(this, tr("Open Audio"), "/home", tr("WAV Files (*.wav)"));
    ui->statusBar->showMessage("File " + currentFileName + " is loaded", 3000);

    // initialize our custom stream
    eq.streamFromFile(currentFileName.toStdString());
}

void MainWindow::on_playButton_clicked()
{
    // set eq
    ui->statusBar->showMessage("Please wait, we are preparing the equalization...");
    ui->statusBar->clearMessage();
    // play the file
    eq.play();
//    while (eq.getStatus() == EqualizerStream::Playing)
//        sf::sleep(sf::seconds(0.1f));
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::on_stopButton_clicked()
{
    ui->playButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    eq.stop();
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    coeffs[0] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    coeffs[1] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    coeffs[2] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_4_sliderMoved(int position)
{
    coeffs[3] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_5_sliderMoved(int position)
{
    coeffs[4] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_6_sliderMoved(int position)
{
    coeffs[5] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_7_sliderMoved(int position)
{
    coeffs[6] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_8_sliderMoved(int position)
{
    coeffs[7] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_9_sliderMoved(int position)
{
    coeffs[8] = (position) / 10.0;
}

void MainWindow::on_verticalSlider_10_sliderMoved(int position)
{
    coeffs[9] = (position) / 10.0;
}
