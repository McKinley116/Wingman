#include "wingman.h"
#include "ui_wingman.h"
#include <QInputDialog>
#include <QMessageBox>

wingman::wingman(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wingman)
{
    ui->setupUi(this);

    connect (ui -> generateEMGButton, &QPushButton::clicked, this, &wingman::onGenerateEMGButtonClicked);
}

void wingman::onGenerateEMGButtonClicked(){
    int numSample = ui > sampleSizeLineEdit->text().toInt();
    QString inputText = ui->gestureNumberLineEdit->text();

    //Show loading and instructions
    showLoadingAnimation();
    showGestureInstructions();

    bool conversionOK;
    int gestureNumber = inputText.toInt(&conversionOK);

    if (conversionOK) {

        Gesture selectedGestures;

        switch (gestureNumber){
        case 1:
            selectedGestures = FIST;
            break;
        case 2:
            selectedGestures = OPEN;
            break;
        case 3:
            selectedGestures = TWO_FINGER_PINCH;
            break;
        case 4:
            selectedGestures = THREE_FINGER_PINCH;
            break;
        case 5:
            selectedGestures = POINTING;
            break;
        case 6:
            selectedGestures = HOOK;
            break;
        case 7:
            selectedGestures = THUMBS_UP;
            break;
        case 8:
            selectedGestures = RING_FINGER_GRASP;
            break;
        }else{
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for gesture number.");
    }

    //Generate EMG signal
    std::vector<double> timescan(numSample);
    double time = 0.0;
    std::vector<double> emgSignal = generateEMGSignal(numSample, selectedGestures, timescan, time );

    displayEMGSignal(emgSignal, selectedGestures);
}

std::vector<double> wingman::generateEMGSignal(int numSample, Gesture gesture, std::vector<double>& timescan, double& time)
{
    bool ok;
    double cycles = QInputDialog::getDouble(this, "Enter Cycles", "Please enter how long it took you to exert this motion in seconds:", 0.0, 0.0, 1000.0, 2, &ok);
    if (!ok)
        return std::vector<double>();
    double duration = QInputDialog::getDouble(this, "Enter Duration", "Please enter how long it took you to exert this motion in seconds:", 0.0, 0.0, 1000.0, 2, &ok);
    if (!ok)
        return std::vector<double>(); // Return empty vector if user cancels input

    time = duration;

    // Generate EMG signal based on user input
    std::vector<double> emgSignal(numSample);
    for (int x = 0; x < emgSignal.size(); x++) {
        emgSignal[x] = cycles / duration;
    }

    // Apply distortion to the EMG signal
    emgSignal = distortion(emgSignal, 50, 1, timescan);

    return emgSignal;
}

void wingman::displayEMGSignal(const std::vector<double>& emgSignal, Gesture selectedGesture)
{
   //Implement display
}

void wingman::showLoadingAnimation()
{
    // Implement loading animation display code...
}

void wingman::showGestureInstructions()
{
    // Implement gesture instructions display code...
}

wingman::~wingman()
{
    delete ui;
}
