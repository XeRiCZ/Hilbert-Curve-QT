#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Vector2.h"
#include "Drawer.h"
#include "HilbertCurve.h"
#include "SierpinskiCurve.h"
#include <QSlider>
#include <QMainWindow>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include <QLabel>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    bool isAnimating;
    ~MainWindow();

private:
    // Základní proměnné programu
    Ui::MainWindow *ui;
    Drawer * drawer;
    HilbertCurve * hilbertCurve;
    SierpinskiCurve * sierpinskiCurve;
    int iterations;  // počet iterací dané křivky

    // Proměnné potřebné pro animaci vykreslování křivky
    int animatedIndex;
    Vector2 actualPosition;
    bool actualPositionSet;
    QTimer * animationTimer;

    // QT widgety - prvky GUI
    QSlider * iterationSlider;
    QPushButton * playB;
    QPushButton * stopB;
    QCheckBox * animationCheckBox;
    QSlider * speedSlider;
    Curve * activeCurve;
    QLabel * speedText;
    QProgressBar * progressBar;
    QComboBox * comboBox;



private slots:
    // Metody určující chování programu
    void handleSliderChange();
    void handleCurveChange();
    void handleAnimationChange();
    void updateAnimations();
    void stop();
    void play();
};

#endif // MAINWINDOW_H
