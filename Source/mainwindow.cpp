#ifndef MAIN_WINDOW_CPP
#define MAIN_WINDOW_CPP

#endif // MAIN_WINDOW_CPP
#include <QTableView>
#include<iostream>
#include "mainwindow.h"
#include "mymodel.h"
#include<iostream>
#include<vector>
#include<QPushButton>
#include<QHeaderView>
#include <QDesktopWidget>
#include<QHBoxLayout>
#include<QTableWidget>
#include<QDockWidget>




QRect compress_table(
    QTableView* tableView,
    const QVBoxLayout* lay,
    const int& row_max,
    const int& col_max) {


QDesktopWidget desktop;
int desktop_width = desktop.screen()->width();
int desktop_height = desktop.screen()->height();

int left_margin,right_margin,top_margin,bottom_margin;
lay->getContentsMargins(&left_margin,&top_margin,&right_margin,&bottom_margin);

int extra_height_top = top_margin + tableView->frameWidth();
int extra_height_bottom = bottom_margin + tableView->frameWidth();
int extra_width_left = left_margin + tableView->frameWidth();
int extra_width_right = right_margin + tableView->frameWidth();
int width = tableView->verticalHeader()->width() + extra_width_left + extra_width_right;
int h = tableView->horizontalHeader()->height() + extra_height_top + extra_height_bottom;
for(int column = 0; column < col_max; ++column) {
    width += tableView->columnWidth(column);
}
for(int row = 0; row < row_max; ++row ) {
    h += tableView->rowHeight(row);
}

int xCord,yCord;
if((width - extra_width_left - extra_width_right) > desktop_width) {
    xCord = 0;
    width = desktop_width - extra_width_left - extra_width_right;
} else
    xCord = (desktop_width - width)/2;
if(h - extra_height_top - extra_height_bottom - QStyle::PM_TitleBarHeight > desktop_height) {
    yCord = extra_height_top + QStyle::PM_TitleBarHeight;
    h = desktop_height - (extra_height_top + QStyle::PM_TitleBarHeight + extra_height_bottom);
} else
    yCord = (desktop_height - h)/2;
return QRect(xCord,yCord,width,h);
}




void print_board_main(board brd)

{
    int i = 0;
    int j = 0;
    for (auto v : brd)
    {
        j = 0;
        for (auto x : v)
        {
            std::cout << x;
            j++;
        }
        i++;
        std::cout << std::endl;

    }

}


void MainWindow::checkSol()
{
board solution = myModel->solution_board.config;

for(int i =0;i<solution.size();i++)
{
for(int j=0;j<solution[0].size();j++)
{
  if(solution[i][j]=='-')
   solution[i][j]='*';

else if(solution[i][j]=='?')
   solution[i][j]='-';
}
}

board user_sol = myModel->m_gridData;
//std::cout<<"Solution is"<<std::endl;
//print_board_main(solution);
//std::cout<<"\n\n"<<std::endl;
//std::cout<<"Solution is"<<std::endl;
//print_board_main(user_sol);


bool solution_found=true;
int size = solution.size();
for(int i =0;i<solution.size();i++)
{
for(int j=0;j<solution[0].size();j++)
{
if(solution[i][j]!=user_sol[i][j])
{
solution_found=false;
}
}

}
std::vector<std::pair<int,int>> should_not_be_black;
//std::vector<std::pair<int,int>> should_not_be_while;
std::vector<std::pair<int,int>> should_be_black;
if(solution_found)
label->setText("<h2><font color=green>Correct\nSolution</font></h2>");


else
{
    for(int i =0;i<solution.size();i++)
    {
    for(int j=0;j<solution[0].size();j++)
    {
    if(user_sol[i][j]=='*')
    {
        if(solution[i][j]!='*')
        {
should_not_be_black.push_back(std::pair<int,int>(i,j));
        }
    //solution_found=false;
    }
    if(user_sol[i][j]=='-')
    {
        if(solution[i][j]=='*')
        {
should_be_black.push_back(std::pair<int,int>(i,j));
        }
    //solution_found=false;
    }

    }

    }

if(should_not_be_black.size()>0)
label->setText("<h2><font color=red>Board\nInvalid</font></h2>");
else
{

    QString s="";
for(int i=0;i<should_be_black.size();i++)
{
s.append("(");
//std::cout<<"charshould_be_black[i].first"<<should_be_black[i].first<<std::endl;
s.append(QString::number((should_be_black[i].first)));
s.append(",");
s.append(QString::number(should_be_black[i].second));
s.append(")");
s.append("<br>");
if(i==3)
    break;
}
//label->setWordWrap();
    label->setText("<h2><font color=green>Board\nis valid</font></h2><br> <b>Hint is cells:</b>"+s+" should be black");
}

}

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//std::cout<<"Main Window start"<<std::endl;
    std::vector<std::vector<char>> grid={{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'},{'-','-','-','-','-','-','-','-','-','-'}};
    myModel = new MyModel(this,grid,grid.size(),grid.size());
    QWidget *window = new QWidget;
    QWidget *window_2 = new QWidget;
    QPushButton *button1 = new QPushButton("Clear");
    connect(button1, SIGNAL(clicked()), myModel,SLOT(remove_grid()));
    QPushButton *button2 = new QPushButton("Load File");
    connect(button2, SIGNAL(clicked()), myModel,SLOT(loadFile()));
    QPushButton *button3 = new QPushButton("Check");
    connect(button3, SIGNAL(clicked()), this,SLOT(checkSol()));
    QPushButton *button4 = new QPushButton("Solution");
    connect(button4, SIGNAL(clicked()), myModel,SLOT(giveSolution()));
    //QPushButton *button5 = new QPushButton("Five");

    QPushButton *button5 = new QPushButton("Instructions");
    connect(button5, SIGNAL(clicked()), myModel,SLOT(show_instructions()));


    label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("                                              ");
    label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    QHBoxLayout *layout = new QHBoxLayout;
    QHBoxLayout *layout1 = new QHBoxLayout;
    QVBoxLayout* layout_v2 = new QVBoxLayout;
    layout_v = new QVBoxLayout;
    tableView = new QTableView(this);
    layout->addWidget(button1);
    //layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);

    layout_v->addLayout(layout);

    tableView->setModel(myModel);
    tableView->horizontalHeader()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    QRect x1 =  compress_table(tableView,layout_v,myModel->m_gridData.size(),myModel->m_gridData.size());
    tableView->setMinimumHeight(x1.height());
    tableView->setMinimumWidth(x1.width());
    //tableView->setFrameStyle(QFrame::Box | QFrame::Raised);
    //tableView->setFrameStyle(QFrame::NoFrame);

    layout1->addWidget(tableView);
    layout_v2->addWidget(button2);
    layout_v2->addWidget(button5);
    layout_v2->addWidget(label);
    layout1->addLayout(layout_v2);
    //layout_v->addWidget(tableView,50,Qt::AlignCenter);
    //layout_v->setSizeConstraint(QLayout::SetMinimumSize);
    //layout_v->setGeometry(x1);
    layout_v->addLayout(layout1);
    QWidget* w1 = new QWidget(this);
     w1->setLayout(layout_v);
    setCentralWidget(w1);
    //w->show();
    connect(tableView, SIGNAL(clicked(const QModelIndex &)), myModel, SLOT(onTClicked(const QModelIndex &)));
    //tableView->connect(myModel,SIGNAL())
    connect(myModel, SIGNAL(layoutChanged()), this, SLOT(update_table_after_change()));
   // connect(tableView, SIGNAL(clicked(const QModelIndex &)), myModel, SLOT(onTClicked(const QModelIndex &)));
        //tableView->connect(myModel,SIGNAL())
       // w->connect(myModel, SIGNAL(layoutChanged()), this, SLOT(setWindowTitle(const QString &)));
//std::cout<<"Main Window done"<<std::endl;


}
void MainWindow::update_table_after_change()
{
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    QRect x1 =  compress_table(tableView,layout_v,myModel->m_gridData.size(),myModel->m_gridData.size());
    tableView->setMinimumHeight(x1.height());
    tableView->setMinimumWidth(x1.width());
    label->setText("                                              ");
}
