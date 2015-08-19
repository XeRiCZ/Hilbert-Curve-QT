#include "SierpinskiCurve.h"
#include <QDebug>
#include <time.h>


 std::vector<workPoint> SierpinskiCurve::removeEdges(std::vector<workPoint> toChange){
     // Funkce ktera odebere posledni radek i sloupec
     std::vector<workPoint> output;
     for(int i = 0; i < toChange.size(); i++){
         if(!((i-1)%rowSizeBefore == 0))
            output.push_back(toChange[i]);
     }
    return output;
 }

std::vector<workPoint> SierpinskiCurve::shrinkBase(std::vector<workPoint> toChange){
    // Zmenšení tvaru na čtvrtinovou velikost

    std::vector<workPoint> output;
    for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it){
       //(*it).drawedIndex += ((int) ((*it).drawedIndex / rowSizeBefore)) * rowSizeBefore + (2*((int) ((*it).drawedIndex / rowSizeBefore)));
        //qDebug() << "from " << (*it).drawedIndex << " to " << (((*it).drawedIndex / rowSizeBefore) * rowSize) + ((*it).drawedIndex - (((*it).drawedIndex / rowSizeBefore)* rowSizeBefore));
        qDebug() << "from " << (*it).drawedIndex << " to " << "radek " << ((*it).drawedIndex / rowSizeBefore) * rowSize << "  sloupec " << ((*it).drawedIndex - (((*it).drawedIndex / rowSizeBefore)* rowSizeBefore));
       (*it).drawedIndex = (((*it).drawedIndex / rowSizeBefore) * rowSize) + ((*it).drawedIndex - (((*it).drawedIndex / rowSizeBefore)* rowSizeBefore));

       output.push_back((*it));
    }

    return output;
}

std::vector<workPoint> SierpinskiCurve::setInitPosition(int position,std::vector<workPoint> toChange){
    int difference = position - toChange[0].drawedIndex;
    std::vector<workPoint> output;
    for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it){
       workPoint newWP = (*it);
       newWP.drawedIndex += difference;
       output.push_back(newWP);
    }
    return output;
}

std::vector<workPoint> SierpinskiCurve::increaseCurveIndexes(int increment, std::vector<workPoint> toChange){
    for(std::vector<workPoint>::iterator it = toChange.begin(); it != toChange.end(); ++it)
        (*it).curveIndex += increment;
    lastCurveIndex = toChange[toChange.size()-1].curveIndex;
    return toChange;
}



SierpinskiCurve::SierpinskiCurve(Drawer *d,int * iter,QProgressBar * pb)
{
    drawer = d;
    iterations = iter;
    progressBar = pb;
}

void SierpinskiCurve::generateCurve()
{
    // Vypočet velikosti rastru
    qDebug() <<"Zacinam generovat sierpiskiho krivku";
    int oneSideCount = 7;
    for(int i = 0; i < *iterations-1; i++)
        oneSideCount =(oneSideCount * 2) + 2;
    areas = oneSideCount*oneSideCount;
 qDebug() << "One side count - " << oneSideCount << " number of areas - " << areas;
    float areaWidth = 640.0 / (oneSideCount-*iterations);
    float areaHeight = 480.0 / (oneSideCount-*iterations);

    points.clear();
    notDrawnIDs.clear();

    // Rozsrastrování plochy a oindexování buňek
    // Razstrování probíhá po řádcích od buňky s pozicí (0,1) až po buňku (1,0)  - "od leveho spodniho rohu po pravý horní"

    for(int coefficientY = 0; coefficientY < oneSideCount; coefficientY++)
    {
        for(int coefficientX = 0; coefficientX < oneSideCount; coefficientX++)
        {
            Vector2 newPosition = Vector2(areaWidth * coefficientX  ,480 - (areaHeight * coefficientY) );
            point * newPoint = new point(-1,newPosition);
            points.push_back(newPoint);
        }
    }

    progressBar->setValue(0);
    allWorkPoints.clear();
    allJoints.clear();
    // Vytvoření základního tvaru sierpinskiho křivky (při iteraci 1)
    std::vector<workPoint> base;
    base.push_back(workPoint(1,0));
    base.push_back(workPoint(7,1));
    base.push_back(workPoint(15,2));
    base.push_back(workPoint(22,3));
    base.push_back(workPoint(29,4));
    base.push_back(workPoint(35,5));
    base.push_back(workPoint(43,6));
    base.push_back(workPoint(37,7));
    base.push_back(workPoint(38,8));
    base.push_back(workPoint(39,9));
    base.push_back(workPoint(47,10));
    base.push_back(workPoint(41,11));
    base.push_back(workPoint(33,12));
    base.push_back(workPoint(26,13));
    base.push_back(workPoint(19,14));
    base.push_back(workPoint(13,15));
    base.push_back(workPoint(5,16));
    base.push_back(workPoint(11,17));
    base.push_back(workPoint(10,18));
    base.push_back(workPoint(9,19));
    base.push_back(workPoint(1,20));
    lastCurveIndex = 20;
    // Vytvoření zakladního tvaru spoje
    std::vector<workPoint> baseJoint;
    baseJoint.push_back(workPoint(9,0,true));
    baseJoint.push_back(workPoint(12,1));
    baseJoint.push_back(workPoint(20,2,true));
    baseJoint.push_back(workPoint(41,3));
    baseJoint.push_back(workPoint(47,4,true));
    baseJoint.push_back(workPoint(44,5));
    baseJoint.push_back(workPoint(36,6,true));
    baseJoint.push_back(workPoint(15,7));

    allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());
    //allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());
    rowSize = 7;

    for(int i = 0; i < *iterations-1; i++){
        allWorkPoints.clear();
        allJoints.clear();

        rowSizeBefore = rowSize;
        // Samotný algoritmus generování
        // v podstatě funguje tak, že vezmu zakladni tvar (base) a zkopiruju ho 4x a vlozim je do vsech rohu
        // rohy ve stredu se odstrani

        std::vector<int> notDrawnsMemory = notDrawnIDs;

        // 1. tvar
         rowSize = rowSize*2 + 2;
        base = shrinkBase(base);
 baseJoint = shrinkBase(baseJoint);
        base = setInitPosition(1,base );
        if(*iterations>2)baseJoint = setInitPosition(1,baseJoint);
            base[11].dontDraw = true;
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());
        if(*iterations>2) allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());

        base[11].dontDraw = false;
        /*for(int j = 0; j <= *iterations-1;j++)
             base[11+ 80*j].dontDraw = false;*/
     //   notDrawnIDs.push_back(lastCurveIndex+1);
    //    notDrawnIDs.push_back(11);
        base[0].dontDraw = true;






        // 2. tvar
       if(*iterations>2) baseJoint = increaseCurveIndexes(baseJoint.size(),baseJoint);
        base = increaseCurveIndexes(base.size(),base);
        int  corrector = i-1;
        if(corrector < 0) corrector = 0;
        base = setInitPosition((rowSize * (rowSizeBefore+1 - (corrector*2)) ) +1 ,base );
    //    base = setInitPosition((rowSize * (rowSize - rowSizeBefore - 2))  + (rowSize +1) ,base );
        if(*iterations>2)baseJoint = setInitPosition(((rowSize/2)+1)*rowSize+1,baseJoint );
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());
        if(*iterations>2) allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());
   //    notDrawnIDs.push_back(lastCurveIndex+1);
   //    notDrawnIDs.push_back(37);
        base[0].dontDraw = true;

        // 3. tvar
        base = increaseCurveIndexes(base.size(),base);
        if(*iterations>2)baseJoint = increaseCurveIndexes(baseJoint.size(),baseJoint);
        base =  setInitPosition((rowSize * (rowSize - rowSizeBefore - 2))  + (rowSize +1) + rowSizeBefore + 1,base );
        if(*iterations>2)baseJoint = setInitPosition(((rowSize/2)+1)*rowSize + rowSizeBefore + 3,baseJoint );
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());
        if(*iterations>2) allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());
        base[0].dontDraw = true;
       // notDrawnIDs.push_back(lastCurveIndex+1);
        //notDrawnIDs.push_back(43);

        // 4. tvar
        if(*iterations>2)baseJoint = increaseCurveIndexes(baseJoint.size(),baseJoint);
        base = increaseCurveIndexes(base.size(),base);

        base = setInitPosition(rowSizeBefore+2,base );
        if(*iterations>2)baseJoint = setInitPosition(rowSizeBefore+3,baseJoint);
        allWorkPoints.insert(allWorkPoints.end(),base.begin(),base.end());
        if(*iterations>2) allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());
        base[0].dontDraw = true;
        //notDrawnIDs.push_back(lastCurveIndex+1);
        //notDrawnIDs.push_back(69);

        // Nove spojeni uprostřed
         if(*iterations>1) {
        baseJoint = increaseCurveIndexes(baseJoint.size(),baseJoint);
       // baseJoint = setInitPosition(((rowSize*rowSize)/2) - rowSizeBefore*rowSizeBefore,baseJoint);
        baseJoint = setInitPosition(((rowSize*rowSize)/2) - ((rowSizeBefore/2)*rowSize) - rowSizeBefore/2 + 1,baseJoint);
        allJoints.insert(allJoints.end(),baseJoint.begin(),baseJoint.end());
         }



        // zkopirovani notDrawnIDs

        progressBar->setValue(progressBar->value()+(10 / *iterations));
        base = allWorkPoints;
        baseJoint = allJoints;
    }
    progressBar->setValue(10);



}

bool SierpinskiCurve::vectorContains(int what){
    // Kontrola jestli vektor obsahuje danou hodnotu int
    for(std::vector<int>::iterator it = notDrawnIDs.begin(); it!= notDrawnIDs.end(); ++it)
        if((*it) == what) return true;
    return false;
}

void SierpinskiCurve::drawCurve(bool useSorted)
{
    drawer->Clear();
    qDebug() << "vykresluji krivku";
    // Serazeni
    float addingProgress = points.size() / 40;
    int j = 0;
/*    std::vector<workPoint> sortedVector;
    for(int i = 0; i < areas; i++){
        for(std::vector<workPoint>::iterator it = allWorkPoints.begin(); it != allWorkPoints.end(); ++it)
            if((*it).curveIndex == i) sortedVector.push_back((*it));
        if(j>= addingProgress){
            j = 0;
            progressBar->setValue(progressBar->value()+1);
        }
        else j++;
    }*/
    sortedAnimationPoints.clear();

    Vector2 latestPosition = points[allWorkPoints[0].drawedIndex]->center;
    // Vykresleni
    for(std::vector<workPoint>::iterator it = allWorkPoints.begin(); it != allWorkPoints.end(); ++it){
        if(!(*it).dontDraw)
            drawer->DrawLine(latestPosition, points[(*it).drawedIndex]->center,Qt::black);

        sortedAnimationPoints.push_back(new point(0,points[(*it).drawedIndex]->center,(*it).dontDraw));
        latestPosition = points[(*it).drawedIndex]->center;
        if(j>= addingProgress){
            j = 0;
            progressBar->setValue(progressBar->value()+1);
        }
        else j++;
    }
    j = 0;
   /* for(std::vector<workPoint>::iterator it = allJoints.begin(); it != allJoints.end(); ++it){
        if(!(*it).dontDraw)
            drawer->DrawLine(latestPosition, points[(*it).drawedIndex]->center,Qt::red);
        latestPosition = points[(*it).drawedIndex]->center;
        if(j>= addingProgress){
            j = 0;
            progressBar->setValue(progressBar->value()+1);
        }
        else j++;
    }*/
    progressBar->setValue(100);
}
