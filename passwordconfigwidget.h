#ifndef PASSWORD_CONFIG_WIDGET_H
#define PASSWORD_CONFIG_WIDGET_H

#include "configwidget.h"


#include <QLineEdit>
#include <QHBoxLayout>

class PasswordConfigWidget : public ConfigWidget {
public:
    PasswordConfigWidget(QWidget* parent = nullptr) : ConfigWidget(parent) {
        
        auto layout = new QHBoxLayout;
        setLayout(layout);
        
        edit = new QLineEdit;
        layout->addWidget(edit);
        
    }
    
    
    QString getConfigString() override {
        return "password " + edit->text();
    }
    
    QString getLabel() override {
        return "Server Password";
    }
    
    QLineEdit* edit;
};

#endif // PASSWORD_CONFIG_WIDGET_H
