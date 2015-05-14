#include "fsdialog.h"
#include<QVBoxLayout>
#include<iostream>
#include<string>

FSModelDialog::FSModelDialog(QWidget *parent,std::string* path) :
    QDialog(parent),path_of_file(path)
{



   tree_view = new QTreeView;
   list_view = new QListView;

    dir_model = new QFileSystemModel(this);


    dir_model->setFilter(QDir::NoDotAndDotDot |
                        QDir::AllDirs);


    dir_model->setRootPath("");


   tree_view->setModel(dir_model);




    file_model = new QFileSystemModel(this);


    file_model->setFilter(QDir::NoDotAndDotDot |
                        QDir::Files);


    file_model->setRootPath("");


    list_view->setModel(file_model);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(tree_view);
    lay->addWidget(list_view);
    setLayout(lay);
connect(tree_view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_treeView_clicked(const QModelIndex &)));
connect(list_view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_listView_clicked(const QModelIndex &)));

}


void FSModelDialog::on_treeView_clicked(const QModelIndex &index)
{

    QString path = dir_model->fileInfo(index).absoluteFilePath();
    std::cout<<path.toStdString();
    list_view->setRootIndex(file_model->setRootPath(path));

}


void FSModelDialog::on_listView_clicked(const QModelIndex &index)
{



    QString path = file_model->fileInfo(index).absoluteFilePath();
    *path_of_file = path.toStdString();
    list_view->setRootIndex(file_model->setRootPath(path));
    done(1);

}
