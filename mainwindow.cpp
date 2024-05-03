#include "mainwindow.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime> // For srand(time(0))

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the main window layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    gestureLabel = new QLabel("Please choose a gesture:", this);
    mainLayout->addWidget(gestureLabel);

    displayGestureOptions();

    sampleSizeEdit = new QLineEdit(this);
    sampleSizeEdit->setPlaceholderText("Enter sample size...");
    mainLayout->addWidget(sampleSizeEdit);

    generateButton = new QPushButton("Generate EMG Signal", this);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateEMGSignal);
    mainLayout->addWidget(generateButton);

    setWindowTitle("EMG Signal Generator");
}

MainWindow::~MainWindow()
{
    // Clean up resources
}

void MainWindow::displayGestureOptions()
{
    std::map<Gesture, std::string> gestureNames = {
        {FIST, "Fist"},
        {OPEN, "Open"},
        {TWO_FINGER_PINCH, "Two Finger Pinch"},
        {THREE_FINGER_PINCH, "Three Finger Pinch"},
        {POINTING, "Pointing"},
        {HOOK, "Hook"},
        {THUMBS_UP, "Thumbs Up"},
        {RING_FINGER_GRASP, "Ring Finger Grasp"}
    };

    for (const auto& pair : gestureNames)
    {
        gestureLabel->setText(gestureLabel->text() + "\n" + QString::number(pair.first + 1) + ": " + QString::fromStdString(pair.second));
    }
}

void MainWindow::generateEMGSignal()
{
    int numSample = sampleSizeEdit->text().toInt();
    if (numSample <= 0)
    {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid sample size.");
        return;
    }

    Gesture selectedGesture = static_cast<Gesture>(QInputDialog::getInt(this, "Choose Gesture", "Enter gesture number:", 1, 1, NUM_GESTURES));

    std::vector<double> timescan(numSample);
    double time = 0.0;

    // Simulate generating EMG signal based on user input
    std::vector<double> emgSignal(numSample);
    for (int i = 0; i < numSample; ++i)
    {
        emgSignal[i] = static_cast<double>(qrand()) / RAND_MAX; // Generate random EMG values (replace with actual logic)
    }

    // Apply distortion to the EMG signal
    emgSignal = distortion(emgSignal, 50, 1, timescan);

    // Display the generated EMG signal
    QString resultText = "EMG Signal generated for " + QString::fromStdString(gestureNames[selectedGesture]) + " gesture:\n";
    for (const auto& val : emgSignal)
    {
        resultText += QString::number(val, 'f', 4) + " hz\n";
    }
    QMessageBox::information(this, "Generated EMG Signal", resultText);
}

std::vector<double> MainWindow::distortion(const std::vector<double>& signals, int max, int min, std::vector<double>& timescan)
{
    std::vector<double> distorted(signals.size());
    std::srand(time(0));
    for (int i = 0; i < signals.size(); i++)
    {
        distorted[i] = signals[i];

        double EMF = static_cast<double>(std::rand()) / RAND_MAX;
        EMF = min + EMF * (max + min);
        timescan[i] = EMF;
        distorted[i] = distorted[i] + EMF;
    }
    return distorted;
}