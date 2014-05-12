#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "mytypes.h"

#include <mainwindow.h>



namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    bool connection();
    void checkSettings();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_enterButton_clicked();

private:
    Ui::LoginWindow *ui;
    QString code(char *in,int szin,char *key,int szkey);

    struct param
    {
      QString host;
      QString dbname;
      QString login;
      QString passwd;

    } authparam;

};

#endif // LOGINWINDOW_H
