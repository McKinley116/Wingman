#include "wingman.h"
#include "ui_wingman.h"

Wingman::Wingman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Wingman)
{
    ui->setupUi(this);

    // Connect contributeButton click to openContributeURL slot
    connect(ui->contributeButton, &QPushButton::clicked, this, &Wingman::openContributeURL);
    connect(ui->testButton, &QPushButton::clicked, this, &Wingman::generateEMGSignals);
}

Wingman::~Wingman()
{
    delete ui;
}

void Wingman::openContributeURL()
{
    QString url = "https://github.com/McKinley116/Wingman";
    QDesktopServices::openUrl(QUrl(url));
}

void Wingman::generateEMGSignals() {
    bool ok;
    double cycles = QInputDialog::getDouble(this, "Enter Cycles", "Please enter how many cycles of motion occur:", 0.0, 0.0, 1000.0, 2, &ok);
    if (!ok)
        return; // User canceled input

    double duration = QInputDialog::getDouble(this, "Enter Duration", "Please enter how long it took you to exert this motion in seconds:", 0.0, 0.0, 1000.0, 2, &ok);
    if (!ok)
        return; // User canceled input

    double time = duration; // Store the duration as the time parameter

    // Create a vector to store the generated EMG signal
    std::vector<double> timescan(cycles); // Assuming 'cycles' as the size of timescan vector

    // Generate EMG signal
    std::vector<double> emgSignal = generateEMGSignal(cycles, FIST, timescan, time); // Assuming FIST as the default gesture

    // Process the generated EMG signal (e.g., display it)
    displayEMGSignal(emgSignal, FIST); // Assuming FIST as the default gesture
}
}
