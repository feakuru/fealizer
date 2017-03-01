#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    coeffs[0] = 0;
    coeffs[1] = 0;
    coeffs[2] = 0;
    coeffs[3] = 0;
    coeffs[4] = 0;
    coeffs[5] = 0;
    coeffs[6] = 0;
    coeffs[7] = 0;
    coeffs[8] = 0;
    coeffs[9] = 0;
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
    eq.streamFromFile("music.wav");
}

void MainWindow::on_playButton_clicked()
{
    // set eq
    std::cout <<  eq.setTenEqualizerCoeffs(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4], coeffs[5], coeffs[6], coeffs[7], coeffs[8], coeffs[9]) << std::endl;
    // play the file
    stream.play();
    while (stream.getStatus() == MyStream::Playing)
        sf::sleep(sf::seconds(0.1f));
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    coeffs[0] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    coeffs[1] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    coeffs[2] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_4_sliderMoved(int position)
{
    coeffs[3] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_5_sliderMoved(int position)
{
    coeffs[4] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_6_sliderMoved(int position)
{
    coeffs[5] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_7_sliderMoved(int position)
{
    coeffs[6] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_8_sliderMoved(int position)
{
    coeffs[7] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_9_sliderMoved(int position)
{
    coeffs[8] = (position - 50) / 25.0;
}

void MainWindow::on_verticalSlider_10_sliderMoved(int position)
{
    coeffs[9] = (position - 50) / 25.0;
}


