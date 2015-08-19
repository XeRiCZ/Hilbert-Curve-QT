/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHilbert_curve;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QFrame *frame_2;
    QLabel *label_2;
    QSlider *iterationsSlider;
    QLabel *numOfIterations;
    QLabel *label_4;
    QLabel *generationTime;
    QLabel *label_5;
    QProgressBar *progressBar;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QFrame *frame_3;
    QSlider *speedSlider;
    QLabel *speedText;
    QCheckBox *animCheckBox;
    QPushButton *playButton;
    QPushButton *stopButton;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(772, 507);
        MainWindow->setMinimumSize(QSize(772, 507));
        MainWindow->setMaximumSize(QSize(772, 507));
        actionHilbert_curve = new QAction(MainWindow);
        actionHilbert_curve->setObjectName(QStringLiteral("actionHilbert_curve"));
        actionHilbert_curve->setCheckable(true);
        actionHilbert_curve->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 767, 482));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(horizontalLayoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(640, 480));
        graphicsView->setMaximumSize(QSize(640, 480));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        horizontalLayout->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 2, 0, 2);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(label);

        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_3->addWidget(comboBox);

        frame_2 = new QFrame(horizontalLayoutWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1, 0, 145, 13));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        iterationsSlider = new QSlider(frame_2);
        iterationsSlider->setObjectName(QStringLiteral("iterationsSlider"));
        iterationsSlider->setGeometry(QRect(1, 20, 111, 20));
        iterationsSlider->setMinimum(1);
        iterationsSlider->setMaximum(8);
        iterationsSlider->setValue(1);
        iterationsSlider->setOrientation(Qt::Horizontal);
        numOfIterations = new QLabel(frame_2);
        numOfIterations->setObjectName(QStringLiteral("numOfIterations"));
        numOfIterations->setGeometry(QRect(60, 0, 46, 13));
        numOfIterations->setTextFormat(Qt::RichText);
        numOfIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1, 110, 145, 13));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        generationTime = new QLabel(frame_2);
        generationTime->setObjectName(QStringLiteral("generationTime"));
        generationTime->setGeometry(QRect(60, 130, 46, 13));
        generationTime->setTextFormat(Qt::RichText);
        generationTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 50, 145, 13));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        progressBar = new QProgressBar(frame_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(2, 70, 111, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_3->addWidget(frame_2);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 2);
        frame = new QFrame(horizontalLayoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(0, 20, 111, 191));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_3->setLineWidth(2);
        speedSlider = new QSlider(frame_3);
        speedSlider->setObjectName(QStringLiteral("speedSlider"));
        speedSlider->setGeometry(QRect(1, 130, 111, 20));
        speedSlider->setMinimum(0);
        speedSlider->setMaximum(100);
        speedSlider->setValue(15);
        speedSlider->setSliderPosition(15);
        speedSlider->setOrientation(Qt::Horizontal);
        speedText = new QLabel(frame_3);
        speedText->setObjectName(QStringLiteral("speedText"));
        speedText->setGeometry(QRect(1, 110, 145, 13));
        sizePolicy1.setHeightForWidth(speedText->sizePolicy().hasHeightForWidth());
        speedText->setSizePolicy(sizePolicy1);
        speedText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        animCheckBox = new QCheckBox(frame_3);
        animCheckBox->setObjectName(QStringLiteral("animCheckBox"));
        animCheckBox->setGeometry(QRect(0, 0, 70, 17));
        playButton = new QPushButton(frame_3);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setEnabled(true);
        playButton->setGeometry(QRect(10, 40, 91, 23));
        stopButton = new QPushButton(frame_3);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(10, 70, 91, 23));

        verticalLayout_2->addWidget(frame);


        verticalLayout->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 772, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Space Filling Curves", 0));
        actionHilbert_curve->setText(QApplication::translate("MainWindow", "Hilbert curve", 0));
        label->setText(QApplication::translate("MainWindow", "Space filling curve type:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Iterations :", 0));
        numOfIterations->setText(QApplication::translate("MainWindow", "1", 0));
        label_4->setText(QApplication::translate("MainWindow", "Generation time [s] :", 0));
        generationTime->setText(QApplication::translate("MainWindow", "1", 0));
        label_5->setText(QApplication::translate("MainWindow", "Generation progress :", 0));
        speedText->setText(QApplication::translate("MainWindow", "Speed :", 0));
        animCheckBox->setText(QApplication::translate("MainWindow", "Animation", 0));
        playButton->setText(QApplication::translate("MainWindow", "Play", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
