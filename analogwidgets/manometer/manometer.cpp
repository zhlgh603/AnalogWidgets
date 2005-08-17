#include <QtGui>
#include <math.h>
#include <assert.h>
#include "manometer.h"
#define PI 3.141592653589793238512808959406186204433

using namespace Qt;
ManoMeter::ManoMeter(QWidget *parent)
        : QMyAbstractMeter(parent)
{
        m_max=300;
        m_min=0;

	m_maximum=300; // najpierw r�cznie potem seterem by wywo�a� calcMaxMin
  	setMinimum(0);
	calcMaxMin(); // bo nie wiemy czym s� zainicjowane limity

	setValue(0);
        setNominal(80);
	setCritical(220);
	setValueOffset(-100);
	setDigitOffset(105);
	setSuffix(QString(" [bar]"));
	m_digitFont.setPointSize(20);
	m_valueFont.setPointSize(25);

	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Barmeter"));
	resize(311, 311);
	assert(m_max-m_min != 0);
}



void ManoMeter::initCoordinateSystem(QPainter & painter)
{
        int side = qMin(width(), height());
        // inicjalizacja paintera
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(width() / 2, height() / 2);
        painter.scale(side / 335.0, side / 335.0);
}

void ManoMeter::paintBackground(QPainter & painter)
{
	static const int scaleTriangle[6] = { -6,141,6,141,0,129 };
	initCoordinateSystem(painter);

        // Malowanie obwiedni tarczy. Bia�a tarcza z czarn� skal�
        QPen Pen(QColor(0,0,0)); Pen.setWidth(4);
        painter.setPen(Pen);

        QRadialGradient back1(QPointF(0.0,0.0),180.0,QPointF(-35.0,145.0));
	back1.setColorAt(0.0,QColor(250,250,250));
	back1.setColorAt(1.0,QColor(20,20,20));

	QRadialGradient back2(QPointF(0.0,0.0),225.0,QPointF(76.5,135.0));
	back2.setColorAt(0.0,QColor(10,10,10));
	back2.setColorAt(1.0,QColor(250,250,250));

	painter.setBrush(QBrush(back1));
	painter.drawEllipse(-162,-162,324,324);
	painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(back2));
        painter.drawEllipse(-152,-152,304,304);

        QRadialGradient shield(QPointF(0,0),182,QPointF(-12.0,-15.0));
	shield.setColorAt(0.0,Qt::white);
	shield.setColorAt(0.5,QColor(240,240,240));
	shield.setColorAt(1.0,QColor(215,215,215));


	// wewn�trzene ko�o skali
	painter.setBrush(QBrush(shield));
	painter.setPen(Pen);
	painter.drawEllipse(-142,-142,284,284);

	  painter.setPen(Qt::NoPen);
          // nominal
	  painter.setBrush(QColor(0,200,0));
	  assert(m_max-m_min != 0);
	  int angle = (3840 * ( m_nominal - m_min ))/(m_max-m_min);
	  if (m_min <= m_nominal && m_nominal < m_max )
           painter.drawPie(QRect(-141,-141,282,282),-480,3840 - angle % 5760 );
	  // Critical

	  painter.setBrush(QBrush(Qt::red));
	  angle = (3840 * ( m_critical - m_min ))/(m_max-m_min);
	  if ( m_min <= m_critical && m_critical < m_max  )
	  painter.drawPie(QRect(-141,-141,282,282),-480, 3840 - angle % 5760  ); //-480, 3840*( m_max-m_min - critical()-abs(m_min) )/static_cast<double>(m_max-m_min));
	  // bia�a obwiednia
	  painter.setBrush(QBrush(shield));
	  painter.drawEllipse(-129,-129,258,258);

        // Ustawienie si� na pocz�tku skali

        painter.rotate(60.0);

 	// Rysowanie skali kreski
	painter.save();
        painter.setBrush(QBrush(Qt::black));
  	int line_length=10;
	for (int i=0;i<33;i++)
	{
	  painter.setPen(Pen);

          if (i % 4) painter.drawLine(0,140,0,140-line_length);
          else {
	    painter.setPen(Qt::NoPen);
	    painter.drawConvexPolygon(QPolygon(3, scaleTriangle));
	  }

	  painter.rotate(7.5);

	Pen.setWidth(3);

 	  if (i % 2)  line_length=10;
	  else        line_length=5;
	}
	painter.restore();

        // Rysowanie skali liczby .
	if (digitOffset())
        {
          painter.rotate(-60.0);
	  painter.setFont(digitFont());
	  for (int i=0;i<9;i++)
	  {
	    QString val = QString("%1").arg(m_min + i*(m_max - m_min)/8.0 );
	    QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, val);
            painter.save();
	    painter.translate( digitOffset() * cos((5+i)*PI/6.0), digitOffset() * sin((5+i)*PI/6.0));
	    painter.drawText( QPointF( Size.width()/ -2.0,  Size.height() / 4.0), val);
	    painter.restore();
	  }
	}



}// paintBackground

void ManoMeter::paintEvent(QPaintEvent * )
{
	drawBackground();
	QPainter painter(this);
        initCoordinateSystem(painter);
      // --------------------------------------------- ///
	static const int hand[12] = {-4, 0, -1, 129, 1, 129, 4, 0, 8,-50, -8,-50};


        QPainterPath hand_path;
        hand_path.moveTo(QPointF(hand[0],hand[1]));

        for (int i=2;i<10;i+=2)
	 hand_path.lineTo(hand[i],hand[i+1]);

	hand_path.cubicTo ( 8.1,-51.0, 5.0,-48.0,   0.0,-48.0);
	hand_path.cubicTo(  -5.0,-48.0, -8.1,-51.0, -8.0,-50.0);

        // Rysowanie wskaz�wki
	painter.save();
	painter.rotate(60.0);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::black));
   	painter.rotate(  (  (abs(m_min)+value()) * 240.0) / static_cast<double> (m_max - m_min) );

	//painter.drawConvexPolygon(QPolygon(6,hand));
	painter.drawPath(hand_path);

	painter.drawEllipse(-10,-10,20,20);


        painter.restore();// Przywrocenie do wychylenia o 60 stopni

	// Rysowanie wy�wietlanej warto�ci
        if (valueOffset())
        {

	  if (value() >= critical() ) painter.setPen(Qt::red);
	  painter.setFont(valueFont());
          QString Str = prefix() + QString("%1").arg(value()) + suffix();
          QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, Str);
          painter.drawText( QPointF( Size.width() / -2.0,static_cast<int>( 0 - valueOffset())) , Str);
        }
}// paintEvent
