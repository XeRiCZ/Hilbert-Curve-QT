#include "Curve.h"
#include "HilbertCurve.h"
#include <math.h>
#include <QDebug>
#include <time.h>

HilbertCurve::HilbertCurve(Drawer *d,int * iter,QProgressBar * pb)
{
    drawer = d;
    iterations = iter;
    progressBar = pb;
}

std::vector<workPoint> HilbertCurve::sortByDrawIndex(std::vector<workPoint> toChange){
     // Setřízení vektoru podle vykreslovacího indexu (drawIndex)
     std::vector<workPoint> sortedOutput;
     for(int i = 0; i < toChange.size(); i++){
         for(std::vector<workPoint>::iterator it = toChange.begin(); it!=toChange.end(); ++it){
             if((*it).drawedIndex == i) // hodnota drawIndexu je shodná s hodnotou iteratoru i
                 sortedOutput.push_back((*it));
         }
     }
     return sortedOutput;
}

 std::vector<workPoint> HilbertCurve::increaseCurveIndexes(int increment, std::vector<workPoint> toChange){
     // Navýšení indexu křivky (pořadí vykreslování) o hodnotu increment
     for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it)
         (*it).curveIndex += increment;
     return toChange;
 }

 std::vector<workPoint> HilbertCurve::pullUpIndexes(std::vector<workPoint> toChange){
     // Draw Indexy spodního řádku vektoru zůstávají stejné, indexy dalších řádků se musí zvýšit o velikost jednoho řádku.
     // z důvodu zvětšení vykreslovacího vektoru.

     std::vector<workPoint> output;
     int index = 0;
     int incrementalIndex = 0;
     int coeficient = 1;
     for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it){
        if(index>=rowSize){
            workPoint newWP = (*it);
            newWP.drawedIndex += rowSize * coeficient;
            output.push_back(newWP);
            incrementalIndex++;
            if(incrementalIndex >= rowSize){
                coeficient++;
                incrementalIndex = 0;
            }
            //(*it).drawedIndex += rowSize;
        }
        else output.push_back((*it));
        index++;
     }
     return output;
 }

std::vector<workPoint> HilbertCurve::mirrorVertical(std::vector<workPoint> toChange){
    // Vertikální zrcadlení vektoru bodů
    std::vector<workPoint> outputVector;
    int index = 0;
    for(int j = rowSize - 1; j >= 0; j--){
        for(int i = 0; i < rowSize ; i++){
            outputVector.push_back(workPoint(toChange[index].drawedIndex,toChange[(j*rowSize) + i  ].curveIndex));
            index++;
        }
    }
    return outputVector;
}

std::vector<workPoint> HilbertCurve::turn90degreesCW(std::vector<workPoint> toChange){
    // Otočení vektoru bodů o 90° po směru hodinových ručiček
    std::vector<workPoint> turnedVector = toChange;
    int index = 0;
    for(int j = 0; j < rowSize; j++){
        for(int i = 0; i < rowSize; i++){
            workPoint selectedWorkPoint = toChange[ (rowSize - j - 1) + (i * rowSize)  ];
            // Index s pozicemi vykresleni zustava stejny pro kazde pole
            // vektor se otaci pouze s indexy krivky
            turnedVector[index++].curveIndex = selectedWorkPoint.curveIndex;
           // turnedVector.push_back(workPoint(toChange[index++].drawedIndex,selectedWorkPoint.curveIndex));

        }
    }
    return turnedVector;
}

std::vector<workPoint> HilbertCurve::turn90degreesAntiCW(std::vector<workPoint> toChange){
    // Otočení vektoru bodů o 90° proti směru hodinových ručiček
    std::vector<workPoint> turnedVector;
    int index = 0;
    for(int j = 0; j < rowSize; j++){
        for(int i = rowSize; i > 0; i--){
            workPoint selectedWorkPoint = toChange[ (i*rowSize) - (rowSize - j) ];
            // Index s pozicemi vykresleni zustava stejny pro kazde pole
            // vektor se otaci pouze s indexy krivky
            turnedVector.push_back(workPoint(toChange[index++].drawedIndex,selectedWorkPoint.curveIndex));
        }
    }
    return turnedVector;
}

std::vector<workPoint> HilbertCurve::setInitPosition(int position,std::vector<workPoint> toChange){
    // Pozicování vektoru bodů na určitou pozici na plátně ( drawedIndex na který se vektor přesune )
    int difference = position - toChange[0].drawedIndex; // rozdíl mezi dosavadní pozicí a novou pozicí
    std::vector<workPoint> output;
    for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it){
       workPoint newWP = (*it);
       newWP.drawedIndex += difference;
       output.push_back(newWP);
    }
    return output;
}

void debugCurve(std::vector<workPoint> debugged){
    // Pomocná funkce pro debugování
    qDebug() << "Debug Curve";
    for(std::vector<workPoint>::iterator it = debugged.begin(); it != debugged.end(); ++it)
        qDebug() << "Work point pointing on drawIndex : " << (*it).drawedIndex << " ; curveIndex : " << (*it).curveIndex;

}

void HilbertCurve::generateCurve()
{
    qDebug() << "Začínám generovat hilbertovu křivku o složitosti" + *iterations;
    // Funkce která rozrastruje plátno na požadovaný počet buněk
    areas = pow(4,(*iterations));

    float OneSideCount =  sqrt(areas);    // počet řádků , či sloupců

    float areaWidth = 640.0 / OneSideCount;
    float areaHeight = 480.0 / OneSideCount;

    points.clear();

    // Rozsrastrování plochy a oindexování buňek
    // Razstrování probíhá po řádcích od buňky s pozicí (0,1) až po buňku (1,0)  - "od leveho spodniho rohu po pravý horní"

    for(int coefficientY = 0; coefficientY < OneSideCount; coefficientY++)
    {
        for(int coefficientX = 0; coefficientX < OneSideCount; coefficientX++)
        {
            Vector2 newPosition = Vector2(areaWidth * coefficientX + (areaWidth/2),480 - (areaHeight * coefficientY + (areaHeight/2)));
            point * newPoint = new point(-1,newPosition);
            points.push_back(newPoint);
        }
    }

    // °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    // Algoritmus vytvoření hilbertovy křivky
    // °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

    std::vector<workPoint> allWorkPoints;

    // Vytvoření základního tvaru hilbertovy křivky (při iteraci 1)
    std::vector<workPoint> base;
    base.push_back(workPoint(0,0));
    base.push_back(workPoint(1,3));
    base.push_back(workPoint(2,1));
    base.push_back(workPoint(3,2));

    progressBar->setValue(0);
    allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());

    // Generovani hilbertovy křivky
    // Hilbertova křivka je vytvořena ve 4 krocích, kdy vysledny tvar křivky z předšlé iterace je 4x "poskládán" do tvaru čtverce.
    // Každý z těchto tvarů je rotován aby vykreslil vysledny objekt
    clock_t start, finish;
    for(int i = 0; i < *iterations-1; i++){ // provedení jedné iterace generování
        allWorkPoints.clear();
        rowSize = sqrt(base.size());    // Nastavení počtu bodů jednoho řádku (či sloupce)
        start = clock();
        base = setInitPosition(0,base);  
        // Jelikož se vykreslovaci pole zvětšilo oproti minule iteraci, je nutno upravit ukazovaci indexy
        base = pullUpIndexes(base);


        //1. část čtverce (čtvrtina vlevo dole)
        // -----------------------------------------
        base = turn90degreesCW(base);
        base = mirrorVertical(base);
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end()); // Zařazení base do vektoru všech workPointu

        // 2. část čtverce (čtvrtina vlevo nahoře)
        // -----------------------------------------
        base = increaseCurveIndexes(base.size(),base); // Navýšení indexů pro další tvar
        base = setInitPosition(rowSize*(rowSize*2),base); // Posunutí dalšího tvaru nad předchozí
        base = mirrorVertical(base); // Zrcadlení
        base = turn90degreesAntiCW(base); // Rotace proti směru hod. ruč
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end()); // Zařazení base do vektoru všech workPointu

        // 3. část čtverce (čtvtina vpravo nahoře)
        // -----------------------------------------
        base = increaseCurveIndexes(base.size(),base); // Navýšení indexů pro další tvar
        base = setInitPosition(rowSize*(rowSize*2) + rowSize,base); // Posunutí dalšího tvaru vedle předchozího
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end()); // Zařazení base do vektoru všech workPointu

        // 4. část čtverce (čtvtina vpravo dole)

        base = increaseCurveIndexes(base.size(),base); // Navýšení indexů pro další tvar
        base = setInitPosition(rowSize,base); // Posunutí dalšího tvaru pod předchozí tvar
        base = turn90degreesAntiCW(base); // Rotace proti směru hod. ruč
        base = mirrorVertical(base); // Zrcadlení
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end()); // Zařazení base do vektoru všech workPointu



        // Hotovo, iterace byla provedena
        // Nyní je potřeba nachystat vše potřebné pro další iteraci
        // Seřadit pole podle drawIndexu

        // base je nyní všechen vygenerovaný obsah
        base = allWorkPoints;
        finish = clock();
        qDebug() << "   iterace [" << i+1 <<"] cas generovani : "
                 << ((double)(finish - start))/CLOCKS_PER_SEC;
        start = clock();
        if(i != *iterations - 2) base = sortByDrawIndex(base);
        finish = clock();
        qDebug() << "   iterace [" << i+1 <<"] cas trideni : "
                 << ((double)(finish - start))/CLOCKS_PER_SEC;
        progressBar->setValue(progressBar->value() + (int)(10 / *iterations));

    }
    progressBar->setValue(10);

    // Zapsání dat z vektoru <workingPointu> do vektoru <pointu>
    for(std::vector<workPoint>::iterator it = allWorkPoints.begin(); it != allWorkPoints.end(); ++it)
         points[(*it).drawedIndex]->idCurve = (*it).curveIndex;

    qDebug() << "Generovani dokonceno.";
}
