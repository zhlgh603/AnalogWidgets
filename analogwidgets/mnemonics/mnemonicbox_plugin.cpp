    #include "qmnemonicbox.h" 
    #include "qmnemonicbox_plugin.h"     
    #include "../defines.h"  
    /*------------------------------------------------------------------------------------------------
     *			     			MANOMETER    
     *------------------------------------------------------------------------------------------------*/
    
    
    MnemonicBoxPlugin::MnemonicBoxPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void MnemonicBoxPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool MnemonicBoxPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget *MnemonicBoxPlugin::createWidget(QWidget *parent)
    {
        return new MnemonicBox(parent);
    }

    QString MnemonicBoxPlugin::name() const
    {
        return QLatin1String("MnemonicBox");
    }

    QString MnemonicBoxPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon MnemonicBoxPlugin::icon() const
    {
        return QIcon();
    }

    QString MnemonicBoxPlugin::toolTip() const
    {
        return QString();
    }

    QString MnemonicBoxPlugin::whatsThis() const
    {
        return QString();
    }

    bool MnemonicBoxPlugin::isContainer() const
    {
        return false;
    }

    QString MnemonicBoxPlugin::domXml() const
    {
        return QLatin1String("<widget class=\"MnemonicBox\" name=\"MnemonicBox\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>100</width>\n"
                             "   <height>100</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string>Shows value of mnemonic</string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>Shows value of mnemonic</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString MnemonicBoxPlugin::includeFile() const
    {
        return QLatin1String("manemonicbox.h");
    }

    QString MnemonicBoxPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS     
    Q_EXPORT_PLUGIN(MnemonicBoxPlugin)
#endif 
