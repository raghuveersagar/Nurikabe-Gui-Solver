

#include <QBrush>
#include<iostream>
#include<fstream>
#include<string>
#include"fsdialog.h"
#include "mymodel.h"
#include"puzzle.cpp"
#include"nurikabe.h"
#include<QLabel>
#include<QVBoxLayout>

MyModel::MyModel(QObject *parent,std::vector<std::vector<char>> x,int rows,int cols)
    :QAbstractTableModel(parent),ROWS(rows),COLS(cols)
{

    m_gridData=x;
}

//-----------------------------------------------------------------
int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return ROWS;
}

//-----------------------------------------------------------------
int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLS;
}

//-----------------------------------------------------------------
//std::string info="default";
//Qt::GlobalColor x = (Qt::red);
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    //std::cout<<info<<std::endl;
    if (role == Qt::BackgroundRole)
    {

       // std::cout<<"In Data "<<std::endl;
  if (m_gridData[row][col]=='*')  //change background only for cell(1,2)
        {
            QBrush redBackground(Qt::black);

            return redBackground;
        }

  if (m_gridData[row][col]=='-')  //change background only for cell(1,2)
        {
            QBrush redBackground(Qt::white);

            return redBackground;
        }


  //cell_modified_table = false;
}
    if (role == Qt::DisplayRole)
    {

        char c = m_gridData[index.row()][index.column()];
        if(c == '-')
        return QChar(' ');
        else
            return QChar(c);
    }
    return QVariant();
}

//-----------------------------------------------------------------
//! [quoting mymodel_e]
/*bool MyModel::setData(const QModelIndex & index, const QVariant & value, int role)
 //{
    if (role == Qt::EditRole)
     {
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row= 0; row < ROWS; row++)
         {
            for(int col= 0; col < COLS; col++)
             {
                result += m_gridData[row][col] + " ";
            }
        }
        emit editCompleted( result );
    }
    if (role == Qt::BackgroundRole)
    {
  if (index.row() == 2 && index.column() == 2)  //change background only for cell(1,2)
        {
            QBrush redBackground(Qt::black);
            return redBackground;
        }
  //cell_modified_table = false;
}
    return true;
}*/
//! [quoting mymodel_e]

//-----------------------------------------------------------------
//! [quoting mymodel_f]
Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEnabled;
//return NULL;
}




void MyModel::loadFile()
{
//std::string x;
    FSModelDialog* q = new FSModelDialog(0,&path_of_file);
    q->setWindowFlags( Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    //w.setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    q->exec();
    //std::cout<<"path_of_file"<<path_of_file<<std::endl;
if(path_of_file.size()!=0)
    begin_puzzle(path_of_file);
//std::cout<<path_of_file<<std::endl;

}


void MyModel::remove_grid()
{
m_gridData = initial_board->config;
 emit layoutChanged();

}


void MyModel::giveSolution()
{
    m_gridData = solution_board.config;
    for(int i =0;i<m_gridData.size();i++)
    {
    for(int j=0;j<m_gridData[0].size();j++)
    {
      if(m_gridData[i][j]=='-')
       m_gridData[i][j]='*';

    else if(m_gridData[i][j]=='?')
       m_gridData[i][j]='-';
    }
    }

   // print_board_gui(m_gridData);
    emit layoutChanged();


}


void MyModel::show_instructions()
{
    //std::cout<<"Instructions"<<std::endl;
QLabel* label = new QLabel();
//label->setTextFormat(Qt::RichText);
//label->setT
QString* s = new QString("<h2>Nurikabe :</h2><br>");
//s->append("Nurikabe is a puzzle about isolating cells in a rectangular grid to form islands of cells with\n");
s->append("Nurikabe is a puzzle about isolating cells in a rectangular grid to form islands of cells with<br>");
s->append("number of cells specified by the cell around which we form the island.For eg:if the<br>");
s->append("number on the cell says 5, we form an island of 5 cells including that cell. Rest of the grid<br>");
s->append("is filled with river leaving just the islands.");
s->append("The rules are:<br>");
s->append("1.The river should not be broken. It should be continuous.<br>");
s->append("2.The river cannot from a 2x2 grid or higher.<br>");
s->append("3.The river cannot pass through the islands.<br>");
s->append("4.The islands need to completely surrounded by river.<br>");
s->append("5.Solution button reveals the button<br>");
s->append("5.Check button informs if the board is valid or not<br>");

//label->setText("1.quququququququq\n2.dhhdhdhdhdhdhdh\n3.shshshshshshs");
label->setText(*s);
QVBoxLayout* lay = new QVBoxLayout;
lay->addWidget(label);

QDialog qd;
qd.setLayout(lay);
//qd.setWind
qd.exec();

}


void MyModel::onTClicked(const QModelIndex &index)
{
    //std::cout<<"onTableClicked"<<std::endl;
    //QBrush redBackground(Qt::red);
   // myModel->setData(index, redBackground, Qt::BackgroundRole);

    //if(m_gridData[index.row()][index.column()]=='-')
    //index_to_change.emplace(index.row(),index.column());

    //else if(m_gridData[index.row()][index.column()]=='*')
      //      index_to_change.find(pair<int,int>(index.row(),index.column()))

        // tableView->childAt(index.row(),index.column())->
    //        QString cellText = index.data().toString();
    //}

    int row = index.row();
    int col = index.column();
    //std::cout<<"m_gridData[row][col]"<<m_gridData[row][col]<<std::endl;
    if(m_gridData[row][col]=='*')
        m_gridData[row][col]='-';

    else if(m_gridData[row][col]=='-')
                m_gridData[row][col]='*';





}
void MyModel::readInput_gui(const string& filename,board &board_ptr)
{
//std::cout<<"File name"<<filename<<std::endl;
    //filename="10x10.txt";
    std::ifstream inputFile;
    std::string inputLine;
    std::vector<char> vec;
    int i = 0;
    int j = 0;
    inputFile.open(filename, std::ios::in);

    while (!inputFile.eof()) {
        i++;
        std::getline(inputFile, inputLine);

        j = 0;
        for (auto each : inputLine)
        {

            if (each != 13)
            {
                j++;
                vec.push_back(each);
            }

        }

        board_ptr.push_back(vec);


        vec.clear();


    }
inputFile.close();


//std::cout<<"readInput_gui-exit"<<std::endl;

}



void MyModel::print_board_gui(board brd)

{
    int i = 0;
    int j = 0;
    for (auto v : brd)
    {
        j = 0;
        for (auto x : v)
        {
            cout << x;
            j++;
        }
        i++;
        cout << endl;

    }

}



void  MyModel::begin_puzzle(std::string filename)
{
    //std::cout<<"begin_puzzle"<<endl;

initial_board = std::make_shared<board_conf>();
     readInput_gui(filename,initial_board->config);
    //print_board_gui(initial_board->config);
    emit layoutAboutToBeChanged();



    m_gridData = initial_board->config;
    ROWS = m_gridData.size();
    COLS = m_gridData.size();


    //std::cout<<"calling ctor"<<std::endl;
    NurikabePuzzleSolver *p=new NurikabePuzzleSolver(*initial_board,false);
    solution_board = p->solve();
  //print_board_gui(solution_board.config);
    //std::cout<<"returning"<<std::endl;
    emit layoutChanged();

}





//! [quoting mymodel_f]
