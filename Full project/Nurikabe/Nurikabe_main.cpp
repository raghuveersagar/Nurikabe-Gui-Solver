#include "mainwindow.h"
#include<mymodel.h>
#include<puzzle.cpp>
#include <QApplication>
#include <QTableView>
#include"nurikabe.h"
#include<iostream>
#include<QPushButton>
#include<vector>
#include<QHBoxLayout>
#include<QDesktopWidget>
#include<unordered_map>
#include<QVBoxLayout>
#include<QHeaderView>
#include<string>
#include<memory>
#include<fstream>
typedef std::vector<std::vector<char>> board;
typedef std::pair<int, int> pair_int;
typedef std::set<pair_int> set_of_pair;
typedef std::pair<std::pair<int, int>, std::pair<int, int>> pair_of_pair;



std::shared_ptr<board_conf> initial_board;
board_conf solution_board;






int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
   //std::vector<std::vector<QString>> grid={{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""},{"","","","","","","","","",""}};
    //std::vector<std::vector<QString>> grid={{"1","2","","","","1","2"},{"1","2","","","","1","2"},{"1","2","","","","1","2"},{"1","2","","","","1","2"},{"1","2","","","","1","2"},{"1","2","","","","1","2"},{"1","2","","","","1","2"}};
    //std::vector<std::vector<char>> grid={{'1','2',' ',' ',' '},{'1','2',' ',' ',' '},{'1','2',' ',' ',' '},{'1','2',' ',' ',' '},{'1','2',' ',' ',' '}};
    //begin_puzzle();
    //int size_puzzle = initial_board->config.size();
    //QMainWindow* w = new QMainWindow;
   /* myModel = new MyModel(w,grid,5,5);
    QWidget *window = new QWidget;
    QWidget *window_2 = new QWidget;
    QPushButton *button1 = new QPushButton("Clear");

    QPushButton *button2 = new QPushButton("Load File");
    w->connect(button2, SIGNAL(clicked()), myModel,SLOT(loadFile()));
    QPushButton *button3 = new QPushButton("Check");
    QPushButton *button4 = new QPushButton("Try");
    //QPushButton *button5 = new QPushButton("Five");

    QHBoxLayout *layout = new QHBoxLayout;
    QHBoxLayout *layout1 = new QHBoxLayout;
    QVBoxLayout *layout_v = new QVBoxLayout();
    QTableView* tableView = new QTableView(w);
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
    QRect x1 =  adjustTableSize(tableView,layout_v,10,10);
    tableView->setMinimumHeight(x1.height());
    tableView->setMinimumWidth(x1.width());
    //tableView->setFrameStyle(QFrame::Box | QFrame::Raised);
    //tableView->setFrameStyle(QFrame::NoFrame);

    layout1->addWidget(tableView);
    layout1->addWidget(button2);
    //layout_v->addWidget(tableView,50,Qt::AlignCenter);
    //layout_v->setSizeConstraint(QLayout::SetMinimumSize);
    //layout_v->setGeometry(x1);
    layout_v->addLayout(layout1);
    QWidget* w1 = new QWidget(w);
     w1->setLayout(layout_v);
    w->setCentralWidget(w1);*/
//    /w->show();
    //w->connect(tableView, SIGNAL(clicked(const QModelIndex &)), myModel, SLOT(onTClicked(const QModelIndex &)));
    //tableView->connect(myModel,SIGNAL())
   // w->connect(myModel, SIGNAL(layoutChanged()), this, SLOT(setWindowTitle(const QString &)));

    MainWindow w;
    w.setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    w.show();



    return a.exec();
}


/*int begin_puzzle()
{
    //std::cout<<"begin_puzzle"<<endl;
    initial_board = std::make_shared<board_conf>();
    std::string filename="10x10.txt";
    //std::cout << "Filename is " << filename;
    readInput_gui(filename, initial_board->config);
    print_board_gui(initial_board->config);
    //std::cout << "\n\n";
    //std::unordered_map<std::string, set_of_pair> map_pairs;
    //set_of_pair temp_set;
    //temp_set.insert(std::pair<int,int>(2,2));
    //map_pairs.insert(std::pair<std::string, set_of_pair>("positive_cells", temp_set));
    //std::map<pair_int, bool> islands_completed;
    //block_2x2_stream(*board_ptr,pair_int(2,3),map_pairs, islands_completed);
    //print_board(*board_ptr);
    PuzzleSolver<board_conf> *p=new NurikabePuzzleSolver(*initial_board,false);
    solution_board = p->solve();
    cout<<"\n\n"<<endl;
    print_board_gui(solution_board.config);
    //delete p;
    //print_board(*board_ptr);
    //write_output(*board_ptr,"out0.txt");

    //shared_ptr<cell> paren = make_shared<cell>(nullptr, 1, pair<int, int>(1,3));
    //shared_ptr<cell> child = make_shared<cell>(paren.get(), 2, pair<int, int>(1, 4));

    //cout << "" << (child->parent->parent==nullptr) << endl;
    //system("PAUSE");
    return 0;
}

*/
