#ifndef TEAM_DAMAGE_CONFIG_H
#define TEAM_DAMAGE_CONFIG_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

#include "configwidget.h"

class TeamDamageConfigWidget : public ConfigWidget {
public:
    TeamDamageConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {

        auto layout = new QHBoxLayout;
        setLayout(layout);

        checkBox = new QCheckBox;
        layout->addWidget(checkBox);

    }

    QString getConfigString() override {
        return QString("sv_teamdamage ") + (checkBox->isChecked() ? "1" : "0");
    }
    
    QString getLabel() override {
        return "Freindly fire";
    }

    QCheckBox* checkBox;
};

#endif // TEAM_DAMAGE_CONFIG_H

