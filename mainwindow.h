﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QQueue>
#include "equalizer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void on_verticalSlider_sliderMoved(int position);

    void on_verticalSlider_2_sliderMoved(int position);

    void on_verticalSlider_3_sliderMoved(int position);

    void on_verticalSlider_4_sliderMoved(int position);

    void on_verticalSlider_5_sliderMoved(int position);

    void on_verticalSlider_6_sliderMoved(int position);

    void on_verticalSlider_7_sliderMoved(int position);

    void on_verticalSlider_8_sliderMoved(int position);

    void on_verticalSlider_9_sliderMoved(int position);

    void on_verticalSlider_10_sliderMoved(int position);

    void on_stopButton_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_10_valueChanged(int value);

private:

    Ui::MainWindow *ui;

    QString currentFileName;

    double coeffs[10];

    FilteredStream eq;

};

#endif // MAINWINDOW_H
