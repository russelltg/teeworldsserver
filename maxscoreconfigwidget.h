#ifndef MAX_SCORE_CONFIG_WIDGET_H
#define MAX_SCORE_CONFIG_WIDGET_H

#include "configwidget.h"

#include <QHBoxLayout>
#include <QSpinBox>

class MaxScoreConfigWidget : public ConfigWidget {
public:
    MaxScoreConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {
        auto layout = new QHBoxLayout;
        setLayout(layout);
        
        auto spin = new QSpinBox;
        layout->addWidget(spin);
        
        spin->setValue(50);
        spin->setMinimum(0);
        connect(spin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this](int newVal) {
            value = newVal;
        });
        
    };
    
    QString getConfigString() override {
        return "sv_scorelimit " + QString::number(value);
    }
    
    QString getLabel() override {
        return "Max Score";
    }
    
    int value = 50;
};

#endif // MAX_SCORE_CONFIG_WIDGET_H
