/************************************************************************
  			scalesgriddecorator.h - Copyright coder
**************************************************************************/

#ifndef SCALESGRIDDECORATOR_H
#define SCALESGRIDDECORATOR_H

#include "chart/chartdecorator.h"



namespace chart {
namespace Standard {
/**
 * Class ScalesGridDecorator
 * Klasa domalowywuj�ca Skal� oraz Siatk� wykresu
 */
class ScalesGridDecorator : public ChartDecorator {

public:

 /**
  * Konstruktor
  * @param component Pointer na nast�pny dekorator
  */
  ScalesGridDecorator (ChartDecorator * component );

 /** Operacja malowania. Maluje kolejne elementy komponentu Chart. */
  void paint (QPainter & painter, Chart * chart);

protected:

  void paintBackground(QPainter &painter, Chart * chart);
  void paintXScale(QPainter & painter, Chart * chart);
  void paintYScale(QPainter & painter, Chart * chart);
  void paintXGrid  (QPainter & painter, Chart * chart);
  void paintYGrid  (QPainter & painter, Chart * chart);

 //double YScaleHeight();
 private:
  double xScaleHeight;
  double yScaleHeight;
  double yScaleWidth;
  
  double m_min; 
  double m_max; 
  double scaleSize; 
  bool   m_channelsScale ; // okre�la czy jakikoliek kana� ma malowan� skal� 
//   
};
} // chart
} // Standard
#endif //SCALESGRIDDECORATOR_H

