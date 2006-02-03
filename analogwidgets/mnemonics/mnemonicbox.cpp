#include <QtGui> 
#include <iostream>

#include "mnemonicbox.h"
#include "comm/engine.h" // z Bartkom/src/comm/

using namespace std; 
using namespace comm; 

MnemonicBox::MnemonicBox(QWidget * parent) : QWidget(parent)
{
  m_type = none; 
  m_mnemonicname = QString("mnemonic"); 
  m_isVisible = true; 
  m_widget = NULL; 
  m_bridge = NULL; 
  
  //****************
  // DO test�w tylko 
 // setServer("/config.xml");
 // m_mnemonicname = "drugi"; 
  
  //****************
  
  initChildComponent(); 
  
}

void MnemonicBox::setServer  (QString value)
{
   comm::EngineConfigFile( value.toLocal8Bit().data() );
}

QString MnemonicBox::server   ()
{
  QString Str ( comm::EngineConfigFile().c_str()); 
  return Str; 
}

void MnemonicBox::initChildComponent()
{
  
  if (m_bridge) 
  { 
    delete m_bridge; 
    m_bridge = NULL; 
    m_type = none;
  }
  
  try
  {
     m_bridge = CreateMnemonicBridge(m_mnemonicname.toLocal8Bit().data()); 
     string type = m_bridge->property("type");
     char *types[]={"int","double","bool"}; 
     int  m_types[]={int_t,double_t,bool_t}; 
     for (int i=0;i<3;i++)
     if (type==types[i]) m_type = m_types[i]; 
  }
  
  catch (exception & e)
  {
    cout<<"Wyj�tek:"<<e.what()<<endl; 
  }
  
    if (NULL==layout())
    {
      QHBoxLayout * layout = new QHBoxLayout(); 
      layout->setMargin(0);
      layout->setSpacing(0); 
      setLayout(layout);   
    }
  
    if (m_widget)
    {
      layout()->removeWidget(m_widget);
      m_widget->disconnect(); // roz��cza wszystkie sygna�y 
      delete m_widget; 
      m_widget = NULL; 
    }
  
     if (true==m_isVisible)
    {
      switch (m_type)
      { 
         case int_t    : intType()    ; break;
         case double_t : doubleType() ; break; 
         case bool_t   : boolType()   ; break; 
         case none     : noneType()   ; break;
       }
       layout()->addWidget(m_widget); 
   } // if visible 
   else 
      setLayout(NULL);
    
}

void MnemonicBox::intType()
{
   QSpinBox * box =  new QSpinBox(this); 
   connect (this,SIGNAL(valueChanged(int)),box,SLOT(setValue(int)));
   connect (box,SIGNAL(valueChanged(int)),this,SLOT(setValue(int)));
    
     // minimum 
     common::Value v = m_bridge->property("min"); 
     box->setMinimum(v);
   
     // maximum; 
     v = m_bridge->property("max"); 
     box->setMaximum(v); 

     // step 
     v = m_bridge->property("step");
     box->setSingleStep(v);
     
     // default 
     v = m_bridge->property("default");
     box->setValue(v); 
 
   m_widget = box; 
}

void MnemonicBox::doubleType()
{
   QDoubleSpinBox * box = new QDoubleSpinBox(this);
   
   connect (this,SIGNAL(valueChanged(double)),box,SLOT(setValue(double))); 
   connect (box,SIGNAL(valueChanged(double)),this,SLOT(setValue(double))); 
   
  
    // liczba cyfr po przecinku 
   common::Value v = m_bridge->property("digits"); 
   box->setDecimals(v); 
   
   // minimum
   v = m_bridge->property("min");
   box->setMinimum(v);
   
   // maximum; 
   v = m_bridge->property("max"); 
   box->setMaximum(v); 
   
   // step
   v = m_bridge->property("step");
   box->setSingleStep(v);
   
   // default 
   v = m_bridge->property("default");
   box->setValue(v); 

   
   
   m_widget = box; 
}

void MnemonicBox::boolType()
{
   QCheckBox * box =  new QCheckBox("",this);
   connect(this,SIGNAL(checkChanged(bool)),box,SLOT(setChecked(bool))); 
   connect(box,SIGNAL(toggled(bool)),this,SLOT(setChecked(bool))); 
   
   // default 
   common::Value v = m_bridge->property("default");
   box->setChecked(v); 

   m_widget = box; 
    
}
 
void MnemonicBox::noneType()
{
  QLabel * label = new QLabel(m_mnemonicname,this); 
  label->setAlignment(Qt::AlignHCenter);
  m_widget = label;  
}


void MnemonicBox::updateValue()
{
  if (! m_bridge) return; 
  common::Value v = m_bridge->value();
  switch (m_type)
  {
   case int_t   : setValue(v.toInt()) ; break; 
   case double_t: setValue(v.toDouble()) ; break; 
   case bool_t  : setChecked(v); break;
  }
}

void MnemonicBox::setValue (int value) 
{
  if (!m_bridge) return; 
  common::Value v = value; 
  m_bridge->setValue( v.str()); 
  emit valueChanged(value); 
  emit valueChanged((double)value);
  
}

void  MnemonicBox::setValue (double value) 
{
  if (!m_bridge) return; 
  common::Value v = value; 
  m_bridge->setValue( v.str()); 
  
  emit valueChanged(value);
  emit valueChanged((int)value); 
  
}
void MnemonicBox::setChecked (bool value) 
{
  if (!m_bridge) return; 
  common::Value v = value; 
  m_bridge->setValue(v.str()); 
  
  emit checkChanged(value);
}


int MnemonicBox::intValue () const
{
  if (!m_bridge) return 1; 
  common::Value v = m_bridge->value();
  return v; 
}

double MnemonicBox::doubleValue () const
{
  if (!m_bridge) return 1.0;
  common::Value v = m_bridge->value();
  return v;
}

bool MnemonicBox::checked() const
{
  if (!m_bridge) return false; 
  common::Value v = m_bridge->value();
  return v; 
}


QString MnemonicBox::mnemonic () const
{
  return m_mnemonicname;
}
void MnemonicBox::setMnemonic (QString value) 
{
  m_mnemonicname = value; 
  initChildComponent();
  setObjectName(value); 
  update(); 
}


bool MnemonicBox::isVisible () const {  return m_isVisible;  }

void MnemonicBox::setIsVisible (bool value) 
{ 
   m_isVisible = value ; 
   initChildComponent();
   update();
}


void MnemonicBox::paintEvent(QPaintEvent * /*event*/)
{
  
  if (none==m_type && m_isVisible)
  {
      QPainter painter(this); 
      painter.setPen(Qt::black); 
      painter.drawRect(0,0,width()-1,height()-1); 
  }
}// paintEvent 




