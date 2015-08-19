#include "Curve.h"
#include <QProgressBar>

#ifndef SIERPINSKICURVE_H
#define SIERPINSKICURVE_H


// Rozpracovaná Sierpinskiho křivka - bohužel nevyšel čas k jejímu dokončení

class SierpinskiCurve : public Curve
{
    int rowSize;
    int rowSizeBefore;
    int lastCurveIndex;
    std::vector<int> notDrawnIDs;

public:
    SierpinskiCurve(Drawer * d,int * iter,QProgressBar * pb);
    void generateCurve() override;
    void drawCurve(bool useSorted);
    std::vector<workPoint> allWorkPoints;
    std::vector<workPoint> allJoints;

    bool vectorContains(int what);
    std::vector<workPoint> setInitPosition(int position,std::vector<workPoint> toChange);
    std::vector<workPoint> shrinkBase(std::vector<workPoint> toChange);
    std::vector<workPoint> removeEdges(std::vector<workPoint> toChange);
    std::vector<workPoint> increaseCurveIndexes(int increment, std::vector<workPoint> toChange);

};

#endif // SIERPINSKICURVE_H
