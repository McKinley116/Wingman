#include "wingman.h"
#include "ui_wingman.h"

Wingman::Wingman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Wingman)
{
    ui->setupUi(this);

    // Connect contributeButton click to openContributeURL slot
    connect(ui->contributeButton, &QPushButton::clicked, this, &Wingman::openContributeURL);

    /*connect(ui->testButton, &QPushButton::clicked, this, &Wingman::generateEMGSignals);*/

    connect(ui->timeslider, &TimeSlider::timeChanged, this, &Wingman::sliderValueChanged);
    timeSlider = timeslider;
    timeslider-> setRange(1, 60); // sets time
    timeslider-> setSingleStep(1); // sets steps

    connect(ui->timeSlider, &QSlider::valueChanged, this, &Wingman::timeChanged);
  
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

void Wingman::handleTimeChange(int seconds){
    qDebug() << "Selected time:"<< seconds << "seconds";
    ui->timeLabel->setText(QString("Selected Time: %1 seconds").arg(seconds));
}

void Wingman::generateEMGSignals(){
    int selectedSeconds = timeSlider->value();
    qDebug() << "Generating EMG signals for: " << selectedSignal<< " seconds";    
}