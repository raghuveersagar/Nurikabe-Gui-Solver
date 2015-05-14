#ifndef _NURIKABE_H
#define _NURIKABE_H


#include"puzzle.h"
#include<vector>
#include<memory>
#include<functional>
#include<unordered_map>
#include<map>
#include<set>
#include<queue>
typedef std::vector<std::vector<char>> board;
typedef std::set<std::pair<int, int>> set_of_pair;
typedef std::pair<int, int> pair_int;

struct board_conf
{
	board_conf(board c, std::map<std::pair<int, int>, bool> comp_islands, std::queue<std::pair<int, int>> not_comp_islands, std::unordered_map<std::string, set_of_pair> info) :config(c), island_completed_indiv(comp_islands), island_not_completed_indiv(not_comp_islands), board_cells_info_indiv(info){}
	board_conf() = default;
	board config;
	std::map<std::pair<int, int>, bool> island_completed_indiv;
	std::queue<std::pair<int, int>> island_not_completed_indiv;
	std::unordered_map<std::string, set_of_pair> board_cells_info_indiv;

};



class NurikabePuzzleSolver : public PuzzleSolver<board_conf> {
public:
	NurikabePuzzleSolver(board_conf brd,bool p) :
		PuzzleSolver<board_conf>(brd),path(p) { set_up(); }
	//std::vector<Node<board_conf>*> getConfigurations(Node<board_conf>*);
	std::vector<Node<board_conf>*> getConfigurations(Node<board_conf>*,pair_int);
	bool isRequiredConfiguration(board_conf);
    board_conf  solve();
	void printFinalConfig(Node<board_conf> * node);
	void setPath(){ path = true; }
	//void printFinalConfig_bckp(Node<board> * node); //print the configurations leading to the final node.

private:
	void applyRules(board_conf);
	std::vector<std::shared_ptr<board>> initial_steps;
	bool path = false;
	//std::map<std::pair<int,int>,bool> island_completed;
	//std::queue<std::pair<int, int>> island_not_completed;
	//std::unordered_map<std::string, set_of_pair> board_cells_info;
	void set_up();
	std::vector<std::pair<int, int>> postions_to_check;
	
//	void create_rules();

	
};


#endif
