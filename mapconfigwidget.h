#ifndef MAP_CONFIG_WIDGET_H
#define MAP_CONFIG_WIDGET_H

#include "configwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFileInfo>
#include <QComboBox>
#include <QDirIterator>

class MapConfigWidget : public ConfigWidget {
    Q_OBJECT
public:
    
    MapConfigWidget(QString installDir, QWidget* parent = nullptr) : ConfigWidget(parent) {
        
        auto layout = new QHBoxLayout;
        setLayout(layout);
 
        // get the maps
        QDirIterator iter(installDir + "/data/maps");
        QStringList entries;
        while(iter.hasNext()) {
            QString withExt = iter.next();
            if(QDir(withExt).exists()) continue;
            QFileInfo info(withExt);
            if(!info.exists()) continue;
            QString name = info.fileName();
            if(!name.endsWith(".map")) continue;
            name.remove(name.size() - 4, 4); // remove .map
            entries << name;
        }
        entries.sort();
        
        auto combo = new QComboBox;
        combo->addItems(entries);
        connect(combo, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), this, [this](QString newVal) {
            map = newVal;
            mapChanged(newVal);
        });
        layout->addWidget(combo);
        
    }
    
    QString getConfigString() override {
        return "sv_map " + map;
    }
    
    QString getLabel() override {
        return "Map";
    }

    QString map = "dm1";
    
signals:
    void mapChanged(QString newMap);
};

#endif // MAP_CONFIG_WIDGET_H
