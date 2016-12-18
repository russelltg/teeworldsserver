
#ifndef TIME_LIMIT_CONFIG_WIDGET_H
#define TIME_LIMIT_CONFIG_WIDGET_H

#include "configwidget.h"

#include <QHBoxLayout>
#include <QSpinBox>

class TimeLimitConfigWidget : public ConfigWidget {
public:
    TimeLimitConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {
        auto layout = new QHBoxLayout;
        setLayout(layout);
        
        auto spin = new QSpinBox;
        layout->addWidget(spin);
        
        spin->setSuffix(" minutes");
        spin->setValue(50);
        spin->setMinimum(0);
        connect(spin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this](int newVal) {
            value = newVal;
        });
        
    };
    
    QString getConfigString() override {
        return "sv_timelimit " + QString::number(value);
    }
    
    QString getLabel() override {
        return "Time limit";
    }
    
    int value = 50;
};

#endif // TIME_LIMIT_CONFIG_WIDGET_H
