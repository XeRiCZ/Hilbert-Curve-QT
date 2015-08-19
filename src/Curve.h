#include <vector>
#include "Vector2.h"
#include "Drawer.h"
#include <QProgressBar>
#ifndef CURVE_H
#define CURVE_H

struct point // struktura reprezentujici jednu buňku v rastru
{
public:
    Vector2 center;  // 2D pozice středu dané buňky
    int idCurve; // index potrebny pro vykreslení krivky (poradi buňky ve vykreslovani krivky)
    bool dontDraw;
    point(int iCur,Vector2 cen,bool dnDrw = false) : idCurve(iCur),center(cen),dontDraw(dnDrw)
    {
    }
};

struct workPoint // pomocná struktura
{
public:
    int drawedIndex;  // index bodu na plátně
    int curveIndex;  // index - pořadí bodu ve vykreslování křivky
    bool dontDraw;  // nevykresluj
    workPoint(int dI,int cI,bool dnDrw = false) : drawedIndex(dI),curveIndex(cI),dontDraw(dnDrw) {}
};

// Rodičovská třída Curve pro všechny podtřídy (druhy space-filling křivek, aktualně jen Hilbertova)
class Curve
{
protected:
    std::vector<point*> points;        // vektor všech vrcholů dané křivky (buňek v rastru)
    int * iterations;                        // počet iterací dané křivky
    Drawer * drawer;
    int areas;  // celkový počet buňek v rastru
    QProgressBar * progressBar;


public:
    std::vector<point*> sortedAnimationPoints;
    void Draw(bool useSorted);
    Curve();
    virtual void generateCurve() // hlavní funkce pro vygenerování dané křivky
    {
    }
};

#endif // CURVE_H
