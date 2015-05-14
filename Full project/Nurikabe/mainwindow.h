#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include<QMainWindow>
#include<mymodel.h>
#include<QVBoxLayout>
#include<QTableView>
#include<QLabel>

/*Main puzzle window.Create tableview with model and handles signals for updatinmg table and checking solution*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTableView *tableView;
    MyModel* myModel=nullptr;
    QVBoxLayout* layout_v=nullptr;
    QLabel *label=nullptr;
public:
    MainWindow(QWidget *parent = 0);
public slots:
void update_table_after_change();
void checkSol();
    //void showWindowTitle(const QString & title);
    //void onTClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
