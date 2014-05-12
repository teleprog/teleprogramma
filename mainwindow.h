#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytypes.h"

#include "edituser.h"
#include "programblock.h"
#include "addprogram.h"
#include "efirmap.h"
#include "baseparamdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0,int id_user=-1);
    ~MainWindow();

private slots:
void browseClicked();
void editClicked();
void adminClicked();
virtual void showconmenu(const QPoint &pos);
virtual void showefirmenu(const QPoint &pos);
virtual void showusermenu(const QPoint &pos);

void edituserrecord();
void deleteuserrecord();
void newuserrecord();
void editEfir();
void addProgram();
void removeProgram();
void editProgram();
void add(program);
void moveProgramUpFromEfir();
void moveProgramDownFromEfir();
void settingsClicked();
void removeProgramFromEfir();
void toefir();
void showuserprogram();
void saveefir();


private:
    int userid;
    QSqlDatabase *dbconn;
    int roleid;

    Ui::MainWindow *ui;
    QMenu * conmenu;
    QWidget *w;
    QWidget* createWidget();
    QTableWidget *tw;
    QLabel *l;
    QComboBox *listprog;
    void browseProgram(int);
    void alterUsers();
    void initmenu();
    void initsbar();
    void reinit();
    void moveProgramFromEfir(int);
    int currow;
    programblock *pblock;
    efirmap *e;

    };

#endif // MAINWINDOW_H
