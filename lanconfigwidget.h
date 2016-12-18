#ifndef LANCONFIGWIDGET_HPP
#define LANCONFIGWIDGET_HPP

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

#include "configwidget.h"

class LanConfigWidget : public ConfigWidget {
public:
    LanConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {

        auto layout = new QHBoxLayout;
        setLayout(layout);

        auto checkBox = new QCheckBox;
        connect(checkBox, &QCheckBox::stateChanged, this, [this](int newState) {
            isLan = newState == Qt::Checked;
        });
        layout->addWidget(checkBox);

    }

    QString getConfigString() override {
        return QString("sv_register ") + (isLan ? "0" : "1");
    }
    
    QString getLabel() override {
        return "Lan";
    }

    bool isLan = false;
};

#endif // LANCONFIGWIDGET_HPP
