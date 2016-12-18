#ifndef MAXPLAYERSCONFIGWIDGET_H
#define MAXPLAYERSCONFIGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

#include "configwidget.h"

class MaxPlayersConfigWidget : public ConfigWidget {
public:
    MaxPlayersConfigWidget(QWidget* widget = nullptr) : ConfigWidget(widget) {
        
        auto layout = new QHBoxLayout;
        setLayout(layout);
        
        auto spin = new QSpinBox;
        spin->setMinimum(1);
        spin->setMaximum(64);
        spin->setValue(16);
        connect(spin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this](int newVal) {
            max = newVal;
        });
        layout->addWidget(spin);
    }
    
    QString getConfigString() override {
        return QString::fromStdString("sv_max_clients " + std::to_string(max));
    }
    
    QString getLabel() override {
        return "Max Players";
    }

    int max = 16;
};

#endif // MAXPLAYERSCONFIGWIDGET_H
