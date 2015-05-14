/*
 *Dialog window for file selection
 *
 */

#ifndef FSModelDIALOG_H
#define FSModelDIALOG_H

#include <QDialog>
#include <QTreeView>
#include <QFileSystemModel>
#include"nurikabe.h"
#include <QListView>
#include<string>

class FSModelDialog : public QDialog
{
    Q_OBJECT

public:
    FSModelDialog(QWidget *parent = 0,std::string* path=0);
    //~QFileSystemModelDialog();

private slots:
    /*Direcrory view*/
    void on_treeView_clicked(const QModelIndex &index);
    /*File view view*/
    void on_listView_clicked(const QModelIndex &index);

private:

std::string* path_of_file;
    // Make two models instead of one
    // to filter them separately
    QFileSystemModel *dir_model;
    QTreeView* tree_view;
    QListView* list_view;
    QFileSystemModel *file_model;
};

#endif // FSModelDIALOG_H
