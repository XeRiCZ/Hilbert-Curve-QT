#include "Curve.h"
#include <QDebug>
#include <time.h>
Curve::Curve()
{


}

void Curve::Draw(bool useSorted){
    // Seřazení vektoru na základě indexu křivky (poradi v jakem se bude křivka vykreslovat)
    qDebug() << "Zacinam vykreslovat a tridit krivku";
    clock_t start, finish;
        start = clock();

    std::vector<point*> sortedVector;
    float addingProgress = points.size() / 80;  // hodnota která se přičte do progress baru (seřazení je +- 80% času generovaní)
    int j = 0;  // pomocná proměnná pro zvětšování progress baru

    drawer->Clear(); // Vyčištění vykreslovacího plátna

    if(useSorted) sortedVector = sortedAnimationPoints; // již máme seřazený vektor? proto není nutné jej znovu řadit
    else {
        // Seřazení vektoru bodů vygenerované křivky na základě jejich idCurve (pořadí v jakém se mají vykreslit)
        for(int i = 0; i < points.size(); i++){
            point* nextPoint = NULL;
            for(std::vector<point*>::iterator it = points.begin(); it != points.end(); ++it){
                if((*it)->idCurve == i){  // Nalezení bodu s pořadím vykreslení shodným s hodnotou iteratoru i
                    nextPoint = (*it);
                    break;
                }
            }
            if(j>= addingProgress){
                // Zvětšení hodnoty progress baru o 1%
                j = 0;
                progressBar->setValue(progressBar->value()+1);
            }
            else j++;
            // Zařazení bodu do seřazeného vektoru
            sortedVector.push_back((nextPoint));
        }
    }

    // Procházení všech vrcholů a vykreslení jejich propojení
    Vector2 latestPosition = sortedVector[0]->center;   // Pozice A ze které se bude začínat vykreslovat přímka

    addingProgress = sortedVector.size() / 10;  // vykreslení je 10% času generování křivky
    j=0;
    for(std::vector<point*>::iterator it = sortedVector.begin(); it != sortedVector.end(); ++it){
        // Vykreslení přímky z poslední pozice do následujícího bodu
        drawer->DrawLine(latestPosition,(*it)->center,Qt::black);
        latestPosition = (*it)->center;
        if(j>= addingProgress){
            // Zvětšení hodnoty progress baru o 1%
            j = 0;
            progressBar->setValue(progressBar->value()+1);
        }
    }
    finish = clock();
    sortedAnimationPoints = sortedVector;
    qDebug() << "Hotovo. cas vykreslovani : "
         << ((double)(finish - start))/CLOCKS_PER_SEC;
}

