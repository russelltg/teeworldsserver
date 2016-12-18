#ifndef CONFIGWIDGET_HPP
#define CONFIGWIDGET_HPP

#include <QWidget>

class ConfigWidget : public QWidget {
public:
    ConfigWidget(QWidget* parent = nullptr) : QWidget(parent)  {}

    virtual QString getConfigString() = 0;
    virtual QString getLabel() = 0;

};

#endif // CONFIGWIDGET_HPP
