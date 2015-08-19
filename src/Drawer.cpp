#include "Drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Drawer::Drawer(QGraphicsView* qw)
{
    // Konstruktor třídy Drawer
    lineWidth = 1;
    gView = qw;
    gScene = new QGraphicsScene;
    gScene->setSceneRect(0,0,640,480);

    gView->setFixedSize(640, 480);
    gView->setScene(gScene);
}
void Drawer::Clear(){
    // Vyčištění plátna
    gScene->clear();
    gView->show();
}

void Drawer::DrawLine(int startX,int startY,int endX,int endY,int Color)
{
    // Vykreslení přímky z bodu A (startX,startY) do bodu B (endX,endY) s barvou Color
    gScene->addLine(startX, startY, endX, endY, QPen(QBrush(Color),lineWidth));
    gView->show();
}

void Drawer::DrawLine(Vector2 startPosition,Vector2 endPosition,int Color)
{
    // Vykreslení přímky z bodu A (startPosition) do bodu B (endPosition) s barvou Color
    gScene->addLine(startPosition.x, startPosition.y, endPosition.x, endPosition.y, QPen(QBrush(Color),lineWidth));
    gView->show();
}
