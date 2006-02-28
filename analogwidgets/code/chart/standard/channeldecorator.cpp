/************************************************************************
  			channeldecorator.cpp - Copyright coder
**************************************************************************/

#include <QtGui>
#include <QPainterPath>
#include "chart.h"
#include "chart/standard/channeldecorator.h"
#include <cmath>
#include <iostream> 

using namespace std;

using namespace Standard;

/** Operacja malowania. Maluje kolejne elementy komponentu Chart. */


void ChannelDecorator::paint (QPainter & painter, Chart * chart)
{
 if (!chart->doRepaintBackground())
 {
   //painter.save(); 
   unsigned int rh = painter.renderHints();
   if (chart->isPaintOver())  painter.setRenderHint(QPainter::Antialiasing); // w�aczenie antialiasingu

   Channels & channels = chart->channels();
   Channels::iterator i=channels.end();

   while (i--!=channels.begin())
   {
     painter.save();
     painter.setPen(i->m_pen);
     translateToChannel(painter,chart,*i);
     paintChannel(painter,chart,*i);
     painter.restore();
   } // while

   painter.setRenderHint(QPainter::RenderHint(rh)); // wylaczenie antialiasingu
    
 }// if not doRepaintBackground
  painter.restore();
  ChartDecorator::paint(painter,chart); // uruchomienie nast�pnego dekoratora
}

void ChannelDecorator::translateToChannel (QPainter & painter, Chart * chart, Channel & channel)
{
   double xmin,ymin,xmax,ymax,pos;
   pos  = chart->scaleGrid().pos ;
   xmin = chart->scaleGrid().m_min;
   xmax = chart->scaleGrid().m_max;
   ymin = channel.m_min;
   ymax = channel.m_max;

   QRect window = painter.window();
   xfactor = window.width()/(xmax - xmin );
   yfactor = -window.height()/(ymax - ymin);
   dx = -pos * xfactor;
   dy = ymax * -yfactor;


  // painter.scale( window.width()/(xmax - xmin) ,  -window.height()/(ymax-ymin) );
  // painter.translate(-pos,-ymax);
 //  painter.scale( xfactor,  yfactor );
  // painter.translate(dx,dy);

}

bool anyVector (int x1,int x2) 
{
  return abs(x1-x2)>0; 
}

void ChannelDecorator::paintChannel(QPainter & painter, Chart * chart, Channel & channel)
{
  double x,y;

//  double i=chart->scaleGrid().m_min; +  chart->scaleGrid().pos;
  double i = chart->scaleGrid().pos;
  double j=chart->scaleGrid().m_max  + chart->scaleGrid().pos;
  double current_x = 0 ,old_x=-1.0,current_y,old_y,old_X;
  bool init = false,add = false;
  int width =  painter.window().width();
  int count = 0; 
  if (channel.m_data)
   if (channel.m_data->init())
      {
        QPolygonF line;
        while( channel.m_data->next(x,y) && current_x <= width    )
        {
           current_x = x*xfactor+dx;
           current_y = y*yfactor+dy;
	  
           if ( old_x <= 0 && 0 <=current_x) add = true; // jest w oknie 
           // jest pierwszy lub wnosi jaki� wektor przesuni�cia 
           
           if ( !init || ( add && ( anyVector(old_x,current_x) || anyVector(old_y,current_y) )))
           { line.append(QPointF(current_x,current_y)); count++; } 

/*           
           if ( !init || ( add && ( abs(old_x-current_x)>=1.0 ) || (abs(old_y-current_y)>=1.0) ))
                          line.append(QPointF(current_x,current_y));
*/
           old_x = current_x;
           old_y = current_y;
           init = true;
           
           //line.append(QPointF(current_x,current_y));
        }
       // cout<<"Dodalem:"<<line.size()<<endl;
       painter.drawPolyline(line);
      }
    else
     cout<<"Channel:"<<channel.m_name.toLocal8Bit().constData()<<" has no data"<<endl;
   
  //painter.setRenderHint(QPainter::RenderHint(0x0));
}