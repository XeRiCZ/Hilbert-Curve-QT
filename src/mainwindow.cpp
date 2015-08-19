#include "Drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <time.h>
#include "Vector2.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    // Inicializace programu

    actualPosition = Vector2(0,0);
    ui->setupUi(this);
    animationTimer = new QTimer(this);
    actualPositionSet = false;
    iterations = 1;

    // Přiřazení referencí z GUI
    playB = ui->playButton;
    stopB = ui->stopButton;
    animationCheckBox = ui->animCheckBox;
    speedSlider = ui->speedSlider;
    speedText = ui->speedText;
    drawer = new Drawer(ui->graphicsView);
    iterationSlider = ui->iterationsSlider;
    progressBar = ui->progressBar;
    comboBox = ui->comboBox;



    // Vytvoření křivek
    hilbertCurve = new HilbertCurve(drawer,&iterations,progressBar);
    sierpinskiCurve = new SierpinskiCurve(drawer,&iterations,progressBar);
    comboBox->addItem("Hilbert");

    // Prvotní vygenerování křivky
    handleSliderChange();

    // Propojení prvků programu s funkcemi
    connect(iterationSlider,SIGNAL(valueChanged(int)), this, SLOT(handleSliderChange()));
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(handleCurveChange()));
    connect(animationCheckBox,SIGNAL(stateChanged(int)),this,SLOT(handleAnimationChange()));
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(updateAnimations()));
    connect(playB,SIGNAL(released()),this,SLOT(play()));
    connect(stopB,SIGNAL(released()),this,SLOT(stop()));


    animationTimer->start(2);
    handleAnimationChange();

    actualPosition = hilbertCurve->sortedAnimationPoints[0]->center;

}

void MainWindow::handleCurveChange(){
    // Změna vybraného druhu křivky
    iterationSlider->setValue(1);
    handleSliderChange();
}

void MainWindow::handleSliderChange(){
    // Změna počtu iterací
    std::stringstream ss;
    clock_t start, finish;
    iterations = iterationSlider->value() ;
    ss << "<b>" << iterations << "</b>";
    ui->numOfIterations->setText(QString::fromStdString(ss.str()));


    start = clock();
    if(7-iterations <= 1) drawer->lineWidth = 1;
    else drawer->lineWidth = 7 - iterations;

    if(comboBox->currentText() == "Hilbert")
    {
        hilbertCurve->generateCurve();
        hilbertCurve->drawCurve(false);
        activeCurve = hilbertCurve;
    }
    else if (comboBox->currentText() == "Sierpiński"){
        sierpinskiCurve->generateCurve();
        sierpinskiCurve->drawCurve(false);
        activeCurve = sierpinskiCurve;
    }

    finish = clock();
    std::stringstream ss2;
    ss2 << "<b>" <<  ((double)(finish - start))/CLOCKS_PER_SEC << "</b>";
    ui->generationTime->setText(QString::fromStdString(ss2.str()));
    progressBar->setValue(100);
    animatedIndex = 0;
    actualPosition = activeCurve->sortedAnimationPoints[0]->center;
    if(animationCheckBox->isChecked()) play();
}

void MainWindow::handleAnimationChange()
{
    // Zapnutí/vypnutí animací
    if(!animationCheckBox->isChecked())
    {
        animatedIndex = 0;

        //isAnimating = false;
        playB->setEnabled(false);
        stopB->setEnabled(false);
        speedSlider->setEnabled(false);
        speedText->setEnabled(false);
        activeCurve->Draw(false);
    }
    else
    {
        animatedIndex = 0;
        actualPosition = activeCurve->sortedAnimationPoints[0]->center;
         drawer->Clear();
        //isAnimating = true;
        playB->setEnabled(true);
        stopB->setEnabled(true);
        speedSlider->setEnabled(true);
         speedText->setEnabled(true);
         play();
    }

}

void MainWindow::updateAnimations()
{
    // Aktualizace animace vykreslení křivky
    if(isAnimating)
    {
        float oneStepSize = speedSlider->value() / 2.0 ;
        float actualStepPosition = oneStepSize* (iterations/2.0);
        Vector2 positionBefore = actualPosition;
        while(1)
        {
            // Zjistit vzdalenost od aktualniho bodu do dalšího bodu
            positionBefore = actualPosition;
            Vector2 endPosition =  activeCurve->sortedAnimationPoints[animatedIndex+1]->center;
            float Xdis = (endPosition.x - actualPosition.x);
            float Ydis = (endPosition.y - actualPosition.y);
            float distanceToNextPoint = abs(sqrt((Xdis*Xdis) + (Ydis*Ydis)));
            if(actualStepPosition >= distanceToNextPoint){

                // Vzdalenost kroku animace je větší než vzdálenost aktualni pozice k nejbližšímu bodu
                actualStepPosition -= distanceToNextPoint;
                animatedIndex++;
                if(animatedIndex == activeCurve->sortedAnimationPoints.size()-1){
                    // Konec animace
                    isAnimating = false;
                    drawer->DrawLine(positionBefore,activeCurve->sortedAnimationPoints[animatedIndex]->center,Qt::red);
                    animatedIndex = 0;

                    return;
                }
                actualPosition = activeCurve->sortedAnimationPoints[animatedIndex]->center;
            }
            else {
                // Krok animace nedosahl nejbližšího bodu, posuň tedy pozici o velikost oneStepSize

                Vector2 direction = endPosition - actualPosition;
                direction = direction.normalize(direction);
                actualPosition= actualPosition + ( direction * actualStepPosition );
                actualStepPosition = 0;
            }
            // Vykreslení
            drawer->DrawLine(positionBefore,actualPosition,Qt::red);
            if(actualStepPosition <= 0) break;  // konec jednoho kroku animace
        }


    }
   animationTimer->start(10);
}

void MainWindow::play()
{
    // Spusteni animace
    drawer->Clear();
    animatedIndex = 0;
    actualPosition = activeCurve->sortedAnimationPoints[0]->center;
    isAnimating = true;

}

void MainWindow::stop()
{
    // Zastaveni animace
    isAnimating = false;
    animatedIndex = 0;
    actualPosition = activeCurve->sortedAnimationPoints[0]->center;
    activeCurve->Draw(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

