#ifndef MYTYPES_H
#define MYTYPES_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QPushButton>
#include <QMenu>
#include <QTime>
#include <QLabel>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QVector>
#include <QVariant>
#include <QSettings>
#include <unittest.h>

struct program
 {
  int id;
  QString name;
  QTime time;
  int reklama;
  QString comment;
   QString diktor;
 };

extern QSqlDatabase *db;
extern QSqlQuery query;

#endif // MYTYPES_H
