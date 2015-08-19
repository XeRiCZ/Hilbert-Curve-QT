#include <QGraphicsScene>
#include <QGraphicsView>
#include "Vector2.h"

#ifndef DRAWER_H
#define DRAWER_H


// Třída Drawer
//  stará se o vykreslování čar na prvek GraphicsView v hlavním okně

class Drawer {
    private:
        QGraphicsScene* gScene;
        QGraphicsView* gView;


    public:
        // Konstruktor
        Drawer(QGraphicsView* qw);
        float lineWidth;

        // Jednoduché metody, které vykreslí čáru z počátečního bodu (startX,startY)
        // do cílového bodu (endX,endY).
        void DrawLine(int startX,int startY,int endX,int endY,int Color);
        // Nebo z počátečního vektoru do cílového vektoru
        void DrawLine(Vector2 startPosition,Vector2 endPosition,int Color);
        void Clear();

};

#endif // DRAWER_H
