#include "mainwindow.h"
#include "ui_mainwindow.h"

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

// decodes the file into memory
void MainWindow::on_openButton_clicked()
{
    QString currentFileName = QFileDialog::getOpenFileName(this, tr("Open Audio"), "/home", tr("Audio Files (*.wav *.mp3 *.ogg)"));

    //load the file if need be

    ui->statusBar->showMessage("File " + currentFileName + " is loaded", 3000);
}

void MainWindow::on_playButton_clicked()
{
    // play the file
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 1 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 2 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 3 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_4_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 4 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_5_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 5 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_6_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 6 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_7_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 7 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_8_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 8 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_9_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 9 moved to " + std::to_string(position)), 3000);
}

void MainWindow::on_verticalSlider_10_sliderMoved(int position)
{
    ui->statusBar->showMessage(QString::fromStdString("Slider 10 moved to " + std::to_string(position)), 3000);
}


