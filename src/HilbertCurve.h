#include "Curve.h"
#include <QProgressBar>
#ifndef HILBERTCURVE_H
#define HILBERTCURVE_H


// Třída starající se o vygenerování Hilbertovy křivky
class HilbertCurve : public Curve
{
    int rowSize;

public:
    HilbertCurve(Drawer * d,int * iter,QProgressBar * pb);  // konstruktor
    void generateCurve() override;  // hlavní metoda pro vygenerování křivky
    void drawCurve(bool useSorted){
        Draw(useSorted);
    }

    // Pomocné metody nutné pro vygenerování křivky

    // Otáčení vektoru bodů o 90° ve směru / proti směru hodinových ručiček
    std::vector<workPoint> turn90degreesCW(std::vector<workPoint> toChange);
    std::vector<workPoint> turn90degreesAntiCW(std::vector<workPoint> toChange);

    // Zrcadlení vektoru bodů vertikálně či horizontálně
    std::vector<workPoint> mirrorVertical(std::vector<workPoint> toChange);
    std::vector<workPoint> mirrorHorizontal(std::vector<workPoint> toChange);

    // Pozicování vektoru bodů na určitou pozici na plátně ( drawedIndex na který se vektor přesune )
    std::vector<workPoint> setInitPosition(int position,std::vector<workPoint> toChange);
    // Navýšení indexů pořadí vykreslování křivky (curveIndexů)
    std::vector<workPoint> increaseCurveIndexes(int increment, std::vector<workPoint> toChange);

    // Korekce indexů při zvětšení počtu buněk v rastru vykreslovacího plátna
    std::vector<workPoint> pullUpIndexes(std::vector<workPoint> toChange);

    // Seřazení vektoru podle drawIndexu
    std::vector<workPoint> sortByDrawIndex(std::vector<workPoint> toChange);
};

#endif // HILBERTCURVE_H
