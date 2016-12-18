#ifndef GAMEMODECONFIGWIDGET_H
#define GAMEMODECONFIGWIDGET_H

#include "configwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

class GameTypeConfigWidget : public ConfigWidget {
public:
    GameTypeConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {
        auto layout = new QHBoxLayout;
        setLayout(layout);
        auto combo = new QComboBox;
        combo->addItems(QStringList() << "Capture the flag"  << "Team deathmatch" << "Deathmatch");
        connect(combo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int newId) {
            switch(newId) {
                case 0: value = "ctf"; break;
                case 1: value = "tdm"; break;
                case 2: value = "dm"; break;
                default: break;
            }
        });

        layout->addWidget(combo);

        value = "ctf";

    }

    QString getConfigString() override {
        return "sv_gametype " + value;
    }
    
    QString getLabel() override {
        return "Game Type";
    }

    QString value;

};

#endif // GAMEMODECONFIGWIDGET_H
