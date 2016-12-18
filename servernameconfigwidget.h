#ifndef SERVER_NAME_CONFIG_WIDGET_H
#define SERVER_NAME_CONFIG_WIDGET_H

#include "configwidget.h"

    #include <QLineEdit>
    #include <QHBoxLayout>

    class ServerNameConfigWidget : public ConfigWidget {
    public:
        ServerNameConfigWidget(QWidget* parent = nullptr):ConfigWidget(parent) {
            
            auto layout = new QHBoxLayout;
            setLayout(layout);
            
            edit = new QLineEdit;
            layout->addWidget(edit);
            
        }
        
        
        QString getConfigString() override {
            return "sv_name " + edit->text();
        }
        
        QString getLabel() override {
            return "Server Name";
        }
        
        QLineEdit* edit;
    };

#endif // SERVER_NAME_CONFIG_WIDGET_H
