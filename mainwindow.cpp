#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("FeaLizer 0.2beta");
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
    eq.setCoeffs(coeffs);
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
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{
        ui->oldIndicator->setValue(eq.average_values[0]);
        ui->oldIndicator_2->setValue(eq.average_values[1]);
        ui->oldIndicator_3->setValue(eq.average_values[2]);
        ui->oldIndicator_4->setValue(eq.average_values[3]);
        ui->oldIndicator_5->setValue(eq.average_values[4]);
        ui->oldIndicator_6->setValue(eq.average_values[5]);
        ui->oldIndicator_7->setValue(eq.average_values[6]);
        ui->oldIndicator_8->setValue(eq.average_values[7]);
        ui->oldIndicator_9->setValue(eq.average_values[8]);
        ui->oldIndicator_10->setValue(eq.average_values[9]);
        ui->newIndicator->setValue(((unsigned short)eq.average_values[0] + 32767) * coeffs[0] - 32767);
        ui->newIndicator_2->setValue(((unsigned short)eq.average_values[1] + 32767) * coeffs[1] - 32767);
        ui->newIndicator_3->setValue(((unsigned short)eq.average_values[2] + 32767) * coeffs[2] - 32767);
        ui->newIndicator_4->setValue(((unsigned short)eq.average_values[3] + 32767) * coeffs[3] - 32767);
        ui->newIndicator_5->setValue(((unsigned short)eq.average_values[4] + 32767) * coeffs[4] - 32767);
        ui->newIndicator_6->setValue(((unsigned short)eq.average_values[5] + 32767) * coeffs[5] - 32767);
        ui->newIndicator_7->setValue(((unsigned short)eq.average_values[6] + 32767) * coeffs[6] - 32767);
        ui->newIndicator_8->setValue(((unsigned short)eq.average_values[7] + 32767) * coeffs[7] - 32767);
        ui->newIndicator_9->setValue(((unsigned short)eq.average_values[8] + 32767) * coeffs[8] - 32767);
        ui->newIndicator_10->setValue(((unsigned short)eq.average_values[9] + 32767) * coeffs[9] - 32767);
    });
    timer->start();
    // play the file
    eq.play();
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
    if (coeffs[0] == 0)
        coeffs[0] = 0.01; // this fixes the strange filter behavior
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

void MainWindow::on_delay_checkBox_toggled(bool checked)
{
    this->eq.delay_enabled = checked;
}

void MainWindow::on_vibrato_checkBox_toggled(bool checked)
{
    this->eq.vibrato_enabled = checked;
}
