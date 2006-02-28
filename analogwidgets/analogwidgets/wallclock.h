#ifndef WALLCLOCK_H
#define WALLCLOCK_H

#include "qmywidgetwithbackground.h"
 
    class WallClock : public QMyWidgetWithBackground 
    {
        Q_OBJECT
	Q_PROPERTY (QFont digitFont READ digitFont WRITE setDigitFont)
	Q_PROPERTY (QFont dateFont  READ dateFont  WRITE setDateFont)
	Q_PROPERTY (QFont timeFont  READ timeFont  WRITE setTimeFont)
	Q_PROPERTY (QFont dayFont   READ dayFont   WRITE setDayFont)

	Q_PROPERTY (int digitOffset READ digitOffset WRITE setDigitOffset) //RESET resetDigitOffset)
	Q_PROPERTY (int dateOffset  READ dateOffset  WRITE setDateOffset ) //RESET resetDateOffset )
	Q_PROPERTY (int timeOffset  READ timeOffset  WRITE setTimeOffset ) //RESET resetTimeOffset )
	Q_PROPERTY (int dayOffset   READ dayOffset   WRITE setDayOffset  ) //RESET resetDayOffset  )

	Q_PROPERTY (QColor digitColor READ digitColor WRITE setDigitColor)
	Q_PROPERTY (QColor dateColor  READ dateColor  WRITE setDateColor)
	Q_PROPERTY (QColor timeColor  READ timeColor  WRITE setTimeColor)
	Q_PROPERTY (QColor dayColor   READ dayColor   WRITE setDayColor)


    public:
	WallClock(QWidget *parent = 0);

    	QFont digitFont() const    { return m_digitFont;}
  	QFont timeFont () const    { return m_timeFont; }
    	QFont dateFont () const    { return m_dateFont; }
    	QFont dayFont  () const    { return m_dayFont;  }

    	void setDigitFont(QFont f) {        m_digitFont = f; updateWithBackground();}
    	void setTimeFont (QFont f) {        m_timeFont  = f; updateWithBackground();}
    	void setDateFont (QFont f) {        m_dateFont  = f; updateWithBackground();}
	void setDayFont  (QFont f) {        m_dayFont   = f; updateWithBackground();}

	int     digitOffset () const { return m_digitOffset; }
	int      dateOffset () const { return m_dateOffset;  }
	int      timeOffset () const { return m_timeOffset;  }
	int      dayOffset  () const { return m_dayOffset;   }
	void  setDigitOffset(int i)  {        m_digitOffset = i; updateWithBackground();}
	void  setDateOffset (int i)  {        m_dateOffset  = i; updateWithBackground();}
	void  setTimeOffset (int i)  {        m_timeOffset  = i; updateWithBackground();}
	void  setDayOffset  (int i)  {        m_dayOffset   = i; updateWithBackground();}

	QColor    digitColor() const  { return m_digitColor;   }
	QColor    dateColor() const   { return m_dateColor;    }
	QColor    timeColor() const   { return m_timeColor;    }
	QColor    dayColor()  const   { return m_dayColor;     }

	void   setDigitColor(QColor c){        m_digitColor = c; updateWithBackground();}
	void   setDateColor(QColor c) {        m_dateColor = c;  updateWithBackground();}
	void   setTimeColor(QColor c) {        m_timeColor = c;  updateWithBackground();}
	void   setDayColor (QColor c) {        m_dayColor  = c;  updateWithBackground();}



    protected:

	
        void paintEvent(QPaintEvent *event);
	void paintBackground(QPainter & painter);
	void initCoordinateSystem(QPainter & painter);
	 
	
	int resetDigitOffset() const { return 75; }
	int resetDateOffset()  const { return 0;  }
	int resetTimeOffset()  const { return -12;}
	int resetDayOffset()   const { return 29; }


        QFont m_digitFont;
        QFont m_dateFont;
        QFont m_timeFont;
        QFont m_dayFont;

        int   m_digitOffset;
        int   m_dateOffset;
        int   m_timeOffset;
        int   m_dayOffset;

        QColor m_digitColor;
        QColor m_dateColor;
        QColor m_timeColor;
        QColor m_dayColor;
    };
#endif // WALLCLOCK_H