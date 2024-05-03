#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <iostream>
#include <vector>
#include <map>

enum Gesture {
    FIST,
    OPEN,
    TWO_FINGER_PINCH,
    THREE_FINGER_PINCH,
    POINTING,
    HOOK,
    THUMBS_UP,
    RING_FINGER_GRASP,
    NUM_GESTURES
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generateEMGSignal();

private:
    void displayGestureOptions();
    void displayLoadingAnimation();
    std::vector<double> distortion(const std::vector<double>& signals, int max, int min, std::vector<double>& timescan);
    double calculateAverage(const std::vector<double>& vec);

    QLabel *gestureLabel;
    QPushButton *generateButton;
    QLineEdit *sampleSizeEdit;
    QTimer *timer;
};

#endif // MAINWINDOW_H