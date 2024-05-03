#ifndef WINGMAN_H
#define WINGMAN_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <thread>

//Defines Gesture enum
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

//Forward declarations of Ui namespace
QT_BEGIN_NAMESPACE
namespace Ui {
class wingman;
}
QT_END_NAMESPACE

class wingman : public QMainWindow
{
    Q_OBJECT

public:
    explicit wingman(QWidget *parent = nullptr);
    ~wingman();

private slots:
    void onGenerateEMGButtonClicked();

private:
    Ui::wingman *ui;

    //Helper functions
    std::vector<double> generateEMGSignal(int numSample, Gesture gesture, std::vector<double>& timescan, double& time);
    void displayEMGSignal(const std::vector<double>& emgSignal, Gesture selectedGesture);
    void showLoadingAnimation();
    void showGestureInstructions();
};
#endif // WINGMAN_H
