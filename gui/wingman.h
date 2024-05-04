#ifndef WINGMAN_H
#define WINGMAN_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Wingman;
}
QT_END_NAMESPACE

class Wingman : public QMainWindow
{
    Q_OBJECT

public:
    explicit Wingman(QWidget *parent = nullptr);
    ~Wingman();

public slots:
    void generateEMGSignals(); // generate EMGs

private slots:
    void openContributeURL(); // Slot to open GitHub repository URL

    void gestureSelection(int gestureIndex); // gesture choice
    void frequencySelection(); // freq. Hz
    void timeSelection(); // Time

private:
    Ui::Wingman *ui;
    QVector<bool> gestureEnabled; // Tracks state for each gesture
};

#endif // WINGMAN_H
