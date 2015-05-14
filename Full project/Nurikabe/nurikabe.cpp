#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include <unordered_map>
#include <set>
#include<queue>
#include<memory>
#include"nurikabe.h"
#include"puzzle.cpp"
#include<map>


using namespace std;

typedef vector<vector<char>> board;
typedef pair<int, int> pair_int;
typedef set<pair_int> set_of_pair;
typedef pair<pair<int, int>, pair<int, int>> pair_of_pair;

void print_board(board brd);
bool adjacent_rule(board &, unordered_map<string, set_of_pair> &, map<pair<int, int>, bool>&);
bool diagonal_rule(board &, unordered_map<string, set_of_pair> &, map<pair<int, int>, bool>&);
bool isolated_positive_cells_rule(board &, unordered_map<string, set_of_pair> &, map<pair_int, bool>&);
bool isolated_negative_cells_rule(board &, unordered_map<string, set_of_pair> &, map<pair<int, int>, bool>&);
void _1_islands_rule(board &, unordered_map<string, set_of_pair> &, map<pair<int, int>, bool>&);

void isolate_island(board& , unordered_map<string, set_of_pair>&, map<pair<int, int>, bool>&, const set<pair_int>);
bool extend_stream(board &, unordered_map<string, set_of_pair> &, map<pair<int, int>, bool>&);
bool extend_island(board &, unordered_map<string, set_of_pair> &, map<pair_int, bool>&);
bool isolate_island_if_completed(board &, pair_int cell, unordered_map<string, set_of_pair>&,map<pair_int, bool>&);
void write_output(const board& brd, string file_name);
bool block_2x2_stream(board&, pair_int, unordered_map<string, set_of_pair>&, map<pair<int, int>, bool>&);

void ummarked_cells(board& brd)
{
	for (auto &m : brd)
	{

		for (auto &n : m)
		{
			if (n == '-')
				n = '*';
		}
	}
}

bool is_a_connected_stream(board& brd,int total_positive_cells)
{
	
	
	//cout << "total_positive_cells" << total_positive_cells << endl;
	int m = brd.size();
	int n = brd[0].size();
	int total_cells = m*n;
	pair_int cell;
	for (int i = 0; i < m;i++)
	for (int j = 0; j < n;j++)
	if (brd[i][j] == '*')
	{
		cell.first = i;
		cell.second = j;
	}
		 
	queue<pair_int> stream;
	stream.push(cell);
	pair_int temp_cell;
	int row, col;
	pair_int add_cell;
	set<pair_int>set_of_cells_path;
	int negative_cells_count = 0;
	while (!stream.empty())
	{
		temp_cell = stream.front();
		stream.pop();
		row = temp_cell.first;
		col = temp_cell.second;



		if (row + 1 <= m - 1)
		{



			if (set_of_cells_path.find(pair_int(row + 1, col)) == set_of_cells_path.end() && brd[row + 1][col] == '*')
			{

				negative_cells_count++;
				add_cell = pair_int(row+1, col);

				set_of_cells_path.insert(add_cell);
				stream.push(add_cell);
			}
		}


		if (row - 1 >= 0)
		{


			if (set_of_cells_path.find(pair_int(row - 1, col)) == set_of_cells_path.end() && brd[row - 1][col] == '*')
			{
				negative_cells_count++;
				add_cell = pair_int(row - 1, col);


				set_of_cells_path.insert(add_cell);
				stream.push(add_cell);
			}
		}



		if (col + 1 <= n - 1)
		{

			if (set_of_cells_path.find(pair_int(row, col + 1)) == set_of_cells_path.end() && brd[row][col + 1] == '*')
			{
				negative_cells_count++;
				add_cell = pair_int(row, col + 1);


				set_of_cells_path.insert(add_cell);
				stream.push(add_cell);
			}
		}



		if (col - 1 >= 0)
		{

			if (set_of_cells_path.find(pair_int(row, col - 1)) == set_of_cells_path.end() && brd[row][col - 1] == '*')
			{
				negative_cells_count++;
				add_cell = pair_int(row, col - 1);


				set_of_cells_path.insert(add_cell);
				stream.push(add_cell);


			}



		}


	}

	//cout << "total_cells " << total_cells << endl;
	//cout << "total_positive_cells" << total_positive_cells << endl;
	//cout << "negative_cells_count" << negative_cells_count << endl;

	return (total_cells - total_positive_cells == negative_cells_count);

}

bool NurikabePuzzleSolver::isRequiredConfiguration(board_conf brd)
{
	//cout << "Inside isRequiredConfiguration" << endl;
	//print_board(brd.config);
	//cout << "\n\n";
	board brd_c = brd.config;
	//map<pair_int,bool> completed = brd.island_completed_indiv;
	//queue<pair_int> not_completed = brd.island_not_completed_indiv;
	int total_positive_cells=0;
	
	
	for (int i = 0; i<brd_c.size(); i++)
	{
		for (int j = 0; j<brd_c[0].size(); j++)
		{
			if ((brd_c[i][j] > '0') && (brd_c[i][j] <= '9'))
				total_positive_cells += (brd_c[i][j] - 48);
			else if (brd_c[i][j] == '-')
				brd_c[i][j] ='*';

		}

	}
	//for (auto each : completed)
	//{
		//if(brd_c[each.first.first][each.first.second] > '0' && brd_c[each.first.first][each.first.second] <= '9')
		//total_positive_cells += (brd_c[each.first.first][each.first.second] - 48);
	//}

	
		ummarked_cells(brd_c);
	if (is_a_connected_stream(brd_c, total_positive_cells)){
		//	cout << "Found" << endl;
			//print_board(brd_c);
		//cout << "\n\n";
			
		return true;
		}
		return false;
	
	
	return false;
	//print_board(brd_c);
	//cout << "Incompleted Islands" << brd.island_not_completed_indiv.size()<<endl;
	
	return false;

}
ostream& operator <<(ostream& os, pair<int, int> p1){
	os << "[" << p1.first << "," << p1.second << "]";
	return os;
}

void get_cells(board& brd, set<pair_int>& pairs, function<bool(int)> condition)
{

	int i = 0;
	int j = 0;

	for (auto v : brd)
	{

		j = 0;
		for (auto x : v)
		{
			if (condition(x))
				pairs.insert(pair_int(i, j));
			j++;
		}
		i++;


	}
}

void NurikabePuzzleSolver::set_up()
{
	set_of_pair set_temp;
	auto positive_cells = [](int x){ return (x > 48 && x < 58); };
	unordered_map<std::string, set_of_pair>& map_pairs= startNode->nodeData.board_cells_info_indiv;
	map<pair<int, int>, bool>& comp_islands = startNode->nodeData.island_completed_indiv;
	board& brd = startNode->nodeData.config;
	queue<pair<int, int>>& not_comp_islands = startNode->nodeData.island_not_completed_indiv;

	get_cells(brd, set_temp, positive_cells);
	for (auto cell : set_temp)
		comp_islands.insert(pair<pair<int, int>, bool>(cell, false));
	map_pairs.insert(pair<string, set_of_pair>(string("positive_cells"), set_temp));
	set_temp.clear();
	auto _1_cells = [](int x){ return (x == 49); };
	get_cells(brd, set_temp, _1_cells);
	for (auto cell : set_temp)
		comp_islands[cell] = true;
	map_pairs.insert(pair<string, set_of_pair>(string("1_cells"), set_temp));
	set_temp.clear();
	auto negative_cells = [](int x){ return (x == 42); };
	get_cells(brd, set_temp, negative_cells);
	map_pairs.insert(pair<string, set_of_pair>(string("negative_cells"), set_temp));

	
	
	
	_1_islands_rule(brd, map_pairs, comp_islands);
	//cout << "After 1 cells" << endl;
	//print_board(brd);
	initial_steps.push_back(make_shared<board>(brd));
	//extend_stream(startNode->nodeData, board_cells_info, island_completed);
	//extend_island(startNode->nodeData, board_cells_info, island_completed);
	
	bool changes_from_rules = true;
	

	bool extend_stream_tracker = true;
	bool extend_island_tracker = true;

	bool fire_island_rules = false;
	bool fire_stream_rules = true;
	bool stream_extended_iso = false;
	
	
while (fire_stream_rules)
	{
		 extend_stream_tracker = true;
		 extend_island_tracker = true;
		//i++;
		
		while (fire_stream_rules && extend_stream_tracker)
		{
			extend_stream_tracker = extend_stream(brd, map_pairs,comp_islands);
			initial_steps.push_back(make_shared<board>(brd));
			if (extend_stream_tracker)
				fire_island_rules = true;
			}

		//cout << "Board after extend_stream" << endl;
		//print_board(brd);
		//cout << "\n\n";
		fire_stream_rules = false;
		while (fire_island_rules && extend_island_tracker)
		{
			stream_extended_iso  = isolated_negative_cells_rule(brd, map_pairs, comp_islands);
			initial_steps.push_back(make_shared<board>(brd));
			extend_island_tracker = extend_island(brd, map_pairs, comp_islands);
			initial_steps.push_back(make_shared<board>(brd));
			if (extend_island_tracker)
				fire_stream_rules = true;
		
			
		}
		//cout << "Board after extend_island" << endl;
		//print_board(brd);
		//cout << "\n\n";
		fire_island_rules = false;
	}

	

	/*int i = 0;
	while (true)
	{
		bool adj = false, diag = false, iso_neg = false, iso_pos = false;
			adj= adjacent_rule(startNode->nodeData, board_cells_info, island_completed);
			if (adj)
			{
			}
			
		diag = diagonal_rule(startNode->nodeData, board_cells_info, island_completed);
		if (diag)
			extend_island(startNode->nodeData, board_cells_info, island_completed);
		iso_neg = isolated_negative_cells_rule(startNode->nodeData, board_cells_info, island_completed);
		if (iso_neg)
			extend_island(startNode->nodeData, board_cells_info, island_completed);

		i++;
		if (i == 100)
			break;
	}*/

for (auto each : comp_islands)
{
	if (!each.second)
		not_comp_islands.push(each.first);
	}
//cout << "Board at end of set up" << endl;
/*cout << "Completed Islands" << endl;
for (auto each : comp_islands)
{
	cout << each.first << " --> " << each.second << endl;
}

queue<pair_int> temp_q = not_comp_islands;
cout << "Incomplete Islands" << endl;
while(!temp_q.empty())
{
	cout << temp_q.front() << endl;
	temp_q.pop();
}*/	
cout << "The board after set up  is" << endl; 
//print_board(brd);
cout << "\n\n";

}

bool extend_stream(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
{
	bool stream_extended_adj = false;
	bool stream_extended_diag = false;
	//bool stream_extended_iso = false;
	
	stream_extended_adj = adjacent_rule(brd, map_pairs, island_completed);
	
	
	
	stream_extended_diag = diagonal_rule(brd, map_pairs, island_completed);
	

	
	//stream_extended_iso = isolated_negative_cells_rule(brd, map_pairs, island_completed);
	

	//cout << "stream_extended_adj" << stream_extended_adj << endl;
	//cout << "stream_extended_diag" << stream_extended_diag << endl;
	//cout << "stream_extended_iso" << stream_extended_iso << endl;

	return (stream_extended_adj || stream_extended_diag);
}
bool extend_island(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair_int, bool>& island_completed)
{
	return isolated_positive_cells_rule(brd, map_pairs, island_completed);
}




set_of_pair cells_part_of_incomplete_island(board& brd, pair_int cell)
{

	int m = brd.size();
	int n = brd[0].size();
	queue<pair_int> island;
	island.push(cell);
	pair_int temp_cell;
	int row, col;
	pair_int add_cell;
	set<pair_int>set_of_cells_path;
	while (!island.empty())
	{
		temp_cell = island.front();
		island.pop();
		row = temp_cell.first;
		col = temp_cell.second;



		if (row + 1 <= m - 1)
		{



			if (set_of_cells_path.find(pair_int(row + 1, col)) == set_of_cells_path.end() && brd[row + 1][col] == '?')
			{

				add_cell = pair_int(row + 1, col);


				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
			}
		}


		if (row - 1 >= 0)
		{


			if (set_of_cells_path.find(pair_int(row - 1, col)) == set_of_cells_path.end() && brd[row - 1][col] == '?')
			{

				add_cell = pair_int(row - 1, col);


				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
			}
		}



		if (col + 1 <= n - 1)
		{

			if (set_of_cells_path.find(pair_int(row, col + 1)) == set_of_cells_path.end() && brd[row][col + 1] == '?')
			{

				add_cell = pair_int(row, col + 1);


				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
			}
		}



		if (col - 1 >= 0)
		{

			if (set_of_cells_path.find(pair_int(row, col - 1)) == set_of_cells_path.end() && brd[row][col - 1] == '?')
			{

				add_cell = pair_int(row, col - 1);


				set_of_cells_path.insert(add_cell);
				island.push(add_cell);


			}



		}


	}

	return set_of_cells_path;

}

struct cell
{

	cell(cell* p, int len, pair<int, int> i)
	{
		length = len;
		index = i;
		parent = p;

	}
	cell* parent;
	int length;
	pair<int, int> index;

};


bool check_looping(cell *parent, pair<int, int> child)
{
	while (parent != nullptr)
	{
		if (parent->index == child)
			return false;
		parent = parent->parent;
	}
	return true;
}


bool is_unclaimed_cell(const board& brd,pair_int cell){

	int m = brd.size();
	int n = brd[0].size();
	int row, col;
	set<pair_int>set_of_cells_path;
	set_of_cells_path.insert(cell);
	int limit = 0;
	bool unclaimed_cell = true;
	auto is_it_number = [](const char ch){return (ch > 48 && ch < 58); };
	if (is_it_number(brd[cell.first][cell.second]))
		limit = ((brd[cell.first][cell.second]) - 48);
	queue<pair_int> island;
	island.push(cell);
	pair_int temp_cell;
	pair_int add_cell;
	
	while (!island.empty())
	{
		temp_cell = island.front();
		island.pop();
		row = temp_cell.first;
		col = temp_cell.second;



		if (row + 1 <= m - 1)
		{

			add_cell = pair_int(row + 1, col);
			if (is_it_number(brd[add_cell.first][add_cell.second]))
			{
				return false;
			}


			else if (set_of_cells_path.find(pair_int(row + 1, col)) == set_of_cells_path.end() && brd[row + 1][col] == '?')
			{

				
				
				
				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
				
			}
		}


		if (row - 1 >= 0)
		{

			add_cell = pair_int(row - 1, col);
			if (is_it_number(brd[add_cell.first][add_cell.second]))
			{
				
				return false;
			}

			
			if (set_of_cells_path.find(pair_int(row - 1, col)) == set_of_cells_path.end() && brd[row - 1][col] == '?')
			{
				
				
				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
			}
		}



		if (col + 1 <= n - 1)
		{
			
			add_cell = pair_int(row, col + 1);
			if (is_it_number(brd[add_cell.first][add_cell.second]))
			{
				
				return false;
			}
			
			
			if (set_of_cells_path.find(pair_int(row, col + 1)) == set_of_cells_path.end() && brd[row][col + 1] == '?')
			{
				
				
				set_of_cells_path.insert(add_cell);
				island.push(add_cell);
			}
		}



		if (col - 1 >= 0)
		{

			add_cell = pair_int(row, col - 1);
			if (is_it_number(brd[add_cell.first][add_cell.second]))
			{
				return false;
			}



			if (set_of_cells_path.find(pair_int(row, col - 1)) == set_of_cells_path.end() && brd[row][col - 1] == '?')
			{
				
				
				set_of_cells_path.insert(add_cell);
				island.push(add_cell);


			}



		}


	}


	//if (unclaimed_cell == true)
		//cout << "Unclaimed cell" << cell << endl;
	return unclaimed_cell;
}


queue<cell*> find_all_configurations(board& brd, cell *start, int limit)
{
	int m = brd.size();
	int n = brd[0].size();
	//cout << "m:" << m << "n:" << n << endl;
	//cout << "Limit is: " << limit << endl;
	queue<cell*> queue_c;
	queue_c.push(start);

	cell* temp;
	
	while (!queue_c.empty())
	{
		 temp= queue_c.front();
		if (temp->length == limit)
			break;
		queue_c.pop();
		int row = temp->index.first;
		int col = temp->index.second;

		if (row + 1 <= m - 1 && (brd[row + 1][col] == '-' || (brd[row + 1][col] == '?' && is_unclaimed_cell(brd,pair_int(row+1,col)))) && check_looping(temp->parent, pair<int, int>(row + 1, col)))
		{
			//cout <<"["<<row + 1<<","<<col<<"]" << endl;
			queue_c.push(new cell(temp, temp->length + 1, pair<int, int>(row + 1, col)));

		}

		 if (row - 1 >= 0 && (brd[row - 1][col] == '-' || (brd[row - 1][col] == '?' && is_unclaimed_cell(brd, pair_int(row - 1, col)))) && check_looping(temp->parent, pair<int, int>(row - 1, col)))
		{
			//cout << "[" << row - 1 << "," << col << "]" << endl;
			
			queue_c.push(new cell(temp, temp->length + 1, pair<int, int>(row - 1, col)));

		}

		 if (col + 1 <= n - 1 && (brd[row][col + 1] == '-' || (brd[row][col + 1] == '?' && is_unclaimed_cell(brd,pair_int(row,col+1)))) && check_looping(temp->parent, pair<int, int>(row, col + 1)))
		{
			//cout << "[" << row << "," << col+1 << "]" << endl;
			
			queue_c.push(new cell(temp, temp->length + 1, pair<int, int>(row, col + 1)));
		}

		 if (col - 1 >= 0 && (brd[row][col - 1] == '-' || (brd[row][col - 1] == '?' && is_unclaimed_cell(brd,pair_int(row,col-1)))) && check_looping(temp->parent, pair<int, int>(row, col - 1)))
		{
			//cout << "[" << row << "," << col - 1 << "]" << endl;
			
			queue_c.push(new cell(temp, temp->length + 1, pair<int, int>(row, col - 1)));
		}



	}
	//cout << "Final size" << queue_c.size() << endl;
	//shared_ptr<cell> a = queue_c.front();
	//cout << "Parent Ptr" << a->parent->index<<endl;


	return queue_c;
}


vector<pair<int, int>> get_indices(cell*  temp)
{
	vector<pair<int, int>> indeices;
	set<pair<int, int>> indeices_set;
	while (temp != nullptr)
	{

		indeices.push_back(temp->index);
		temp = temp->parent;
	}

	//cout << " Path " << indeices.size() << endl;
	return indeices;
}


bool is_board_valid(board& brd, pair<int, int> cell,pair_int parent_cell)
{


	int m = brd.size();
	int n = brd[0].size();

	int row = cell.first;
	int col = cell.second;
	if (row + 1 <= m - 1 && ((brd[row + 1][col] == '?' || (brd[row + 1][col] > 47 && brd[row + 1][col] < 58)) && pair_int(row + 1, col) != parent_cell))
		return false;
	if (row - 1 >= 0 && ((brd[row - 1][col] == '?' || (brd[row - 1][col] > 47 && brd[row - 1][col] < 58)) && pair_int(row - 1, col) != parent_cell))
		return false;

	if (col + 1 <= n - 1 && ((brd[row][col + 1] == '?' || (brd[row][col + 1] > 47 && brd[row][col + 1] < 58)) && pair_int(row, col+1) != parent_cell))
		return false;

	if (col - 1 >= 0 && ((brd[row][col - 1] == '?' || (brd[row][col - 1] > 47 && brd[row][col - 1] < 58)) && pair_int(row, col-1) != parent_cell))
		return false;


	return true;
}



/*vector<Node<board_conf>*> NurikabePuzzleSolver::getConfigurations(Node<board_conf>*  brd_conf)
{
	

	/*shared_ptr<Node<board>> new_conf = make_shared<Node<board>>();*/
	
	/*vector<Node<board_conf>*> vector_nodes;
	board temp_board = brd_conf->nodeData.config;
	map<pair_int,bool> comp_islands = brd_conf->nodeData.island_completed_indiv;
	queue<pair_int> in_comp_islands = brd_conf->nodeData.island_not_completed_indiv;
	unordered_map<string, set_of_pair> map_pairs = brd_conf->nodeData.board_cells_info_indiv;
	
	//cout << "getConfigurations-->Board is" << endl;
	
	//cout << "\n\n";
	//print_board(temp_board);
	//cout << "\n\n";
	pair_int incomplete_island;
	if (!in_comp_islands.empty())
	{
		incomplete_island = in_comp_islands.front();
		in_comp_islands.pop();
		//cout << incomplete_island << endl;
		
	

	//cout << "Incomplete Island chosen is " << incomplete_island<<endl;

	set<pair_int> completed_cells_of_incomplete_island = cells_part_of_incomplete_island(temp_board, incomplete_island);

	//cout << "cells_part_of_island" << completed_cells_of_incomplete_island.size() << endl;
	for (auto cell_s : completed_cells_of_incomplete_island)
	{
		//	print_cell(cell_s);
		//cout << " " << endl;
		temp_board[cell_s.first][cell_s.second] = '-';

	}
	//cell *start = new cell(nullptr, 1, pair<int, int>(9, 5));
	queue<cell*> q;
	char original_char = temp_board[incomplete_island.first][incomplete_island.second];
	q = find_all_configurations(temp_board, new cell(nullptr, 1, incomplete_island),(temp_board[incomplete_island.first][incomplete_island.second])-48);
	//cout << "find_all_configurations" << q.size() << endl;
	board board_temp;
	while (!q.empty())
	{
		 board_temp = temp_board;
		cell* front_val = (q.front());
		//cell t = *(q.front()).get();
		q.pop();
		
		
		
		auto vec = get_indices(front_val);
		delete front_val;
		front_val = nullptr;
			bool invalid_board = false;

		for (auto x : vec)
		{
			board_temp[x.first][x.second] = '$';
		}
		board_temp[incomplete_island.first][incomplete_island.second] = original_char;
		


		for (auto x : vec)
		{
			
			if (!(is_board_valid(board_temp, x, original_char)))
			{
				//cout << "Invalid Board" << endl;
				//print_board(board_temp);
				invalid_board = true;
				break;
			}







		}

		for (auto x : vec)
		{
			board_temp[x.first][x.second] = '?';
		}
		//print_board(board_temp);
		//cout << "\n\n";
		if (!invalid_board)
		{
			//cout << "Adding board" << endl;
			
			board_temp[incomplete_island.first][incomplete_island.second] = original_char;
			isolate_island_if_completed(board_temp, incomplete_island, map_pairs, comp_islands);
			board_conf b(board_temp, comp_islands, in_comp_islands, map_pairs);
			//print_board(board_temp);
			//cout << "\n\n";
			vector_nodes.push_back(new Node<board_conf>(brd_conf, b));
		}
			//valid_board_config->push_back(board_temp);


		


		
		

		//print_board(board_temp);
		//cout << "\n\n" << endl;
		
}





	}
	
	
	return vector_nodes;
}

*/


board_conf NurikabePuzzleSolver::solve()
{

	stack<Node<board_conf>*> queueOfConfigs;
	stack<Node<board_conf>*> queueOfConfigs_level;
	Node<board_conf>* finalNode = 0;
	queueOfConfigs.push(startNode);
	bool breakAll = false;
	queue<pair_int> not_completed_islands =  startNode->nodeData.island_not_completed_indiv;
	int i = 0;
	cout << "Not completed islands size()" << not_completed_islands.size() << endl;



    if(isRequiredConfiguration(startNode->nodeData))
        return startNode->nodeData;

	while (!not_completed_islands.empty())
	{
		//if (i == 10)
			//break;
		
		pair_int island_to_check = not_completed_islands.front();
		not_completed_islands.pop();
		bool	isEmpty = not_completed_islands.empty();
        //cout << "Checking Island" << endl;
        //cout << island_to_check << endl;
		i++;
		while (!queueOfConfigs.empty())
		{
			
			Node<board_conf>* node_to_check = queueOfConfigs.top();
			queueOfConfigs.pop();
			vector<Node<board_conf>*> possibleConfigs=getConfigurations(node_to_check, island_to_check);
			
			
			for (vector<Node<board_conf>*>::iterator it = possibleConfigs.begin();
				it != possibleConfigs.end(); it++) {
				if (isEmpty && isRequiredConfiguration((**it).nodeData)) {

					finalNode = *it;

                    //cout << "Final found" << endl;
					ummarked_cells(finalNode->nodeData.config);
                    //print_board(finalNode->nodeData.config);
                    return finalNode->nodeData;
                    //printFinalConfig(finalNode);
					
					breakAll = true;
					break;
				}
				
				//cout << "Board found" << endl;
				//print_board((*it)->nodeData.config);
				//cout << "\n" << endl;
				queueOfConfigs_level.push(*it);
				}


			if (breakAll)
				break;
			
			

		}
		

		queueOfConfigs = queueOfConfigs_level;
		while (!queueOfConfigs_level.empty())
			queueOfConfigs_level.pop();
		

	}


	

	//getConfigurations(top_node);






}
vector<Node<board_conf>*> NurikabePuzzleSolver::getConfigurations(Node<board_conf>*  brd_conf,pair_int island)
{

	board temp_board = brd_conf->nodeData.config;
	vector<Node<board_conf>*> vector_nodes;
	map<pair_int, bool> comp_islands = brd_conf->nodeData.island_completed_indiv;
	queue<pair_int> in_comp_islands = brd_conf->nodeData.island_not_completed_indiv;
	unordered_map<string, set_of_pair> map_pairs = brd_conf->nodeData.board_cells_info_indiv;
	//cout << "Inside getConfigurations" << endl;
	//cout << "Island to check" << endl;
	//cout << island << endl;
	//print_board(brd_conf->nodeData.config);
	//find_all_configurations()

	set<pair_int> completed_cells_of_incomplete_island = cells_part_of_incomplete_island(temp_board,island);
	for (auto cell_s : completed_cells_of_incomplete_island)
	{
		//	print_cell(cell_s);
		//cout << " " << endl;
		temp_board[cell_s.first][cell_s.second] = '-';

	}
	//cell *start = new cell(nullptr, 1, pair<int, int>(9, 5));
	queue<cell*> q;
	char original_char = temp_board[island.first][island.second];
	q = find_all_configurations(temp_board, new cell(nullptr, 1, island),(temp_board[island.first][island.second]) - 48);
	//cout << "All Configurations" << endl;
	board board_temp;
	while (!q.empty())
	{
		board_temp = temp_board;
		cell* front_val = (q.front());
		//cell t = *(q.front()).get();
		q.pop();
		auto vec = get_indices(front_val);
		delete front_val;
		front_val = nullptr;
		bool invalid_board = false;

		for (auto x : vec)
		{
			board_temp[x.first][x.second] = '$';
		}
		board_temp[island.first][island.second] = original_char;

	//cout << "All configuirations" << endl;
		//print_board(board_temp);
		//cout << "\n";
		for (auto x : vec)
		{

			
			
			if (!(is_board_valid(board_temp, x, pair<int, int>(island.first,island.second))))
			{
			//	cout << "Invalid Board" << endl;
				//print_board(board_temp);
				invalid_board = true;
				break;
			}







		}

		for (auto x : vec)
		{
			board_temp[x.first][x.second] = '?';
		}
		board_temp[island.first][island.second] = original_char;
		
		//print_board(board_temp);
		//cout << "\n\n";
		if (!invalid_board)
		{
			//cout << "Adding board" << endl;

			board_temp[island.first][island.second] = original_char;
			isolate_island_if_completed(board_temp, island, map_pairs, comp_islands);
			board_conf b(board_temp, comp_islands, in_comp_islands, map_pairs);
			//print_board(board_temp);
			//cout << "\n\n";
			vector_nodes.push_back(new Node<board_conf>(brd_conf, b));
		}

	}



	//cout << "Final valid Connfigurations" << endl;
	//for (auto x : vector_nodes)
		//print_board(x->nodeData.config);

	
	return vector_nodes;


}





void _1_islands_rule(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
{

	//cout << "Inside i isdlands" << endl;
	int m = brd.size();
	int n = brd[0].size();
	//cout << "m: " << m << " n: " << n << endl;
	const set_of_pair& pairs = map_pairs.at("1_cells");
	set_of_pair& negative_pairs = map_pairs.at("negative_cells");
	bool island_surrounded = false;
	for (auto cell : pairs)
	{
		int row = cell.first;
		int col = cell.second;
		island_surrounded = false;
		if (row + 1 <= m - 1)
		{
			brd[row + 1][col] = '*';
			//cout << "Cell at " << row + 1 << " " << col << endl;
			island_surrounded = true;
			block_2x2_stream(brd, pair_int(row + 1, col), map_pairs, island_completed);
			negative_pairs.insert(pair_int(row + 1,col));
		}
			

		if (row - 1 >= 0)
		{
			island_surrounded = true;
		brd[row - 1][col] = '*';
	//	cout << "Cell at " << row - 1 << " " << col << endl;
		block_2x2_stream(brd, pair_int(row - 1, col), map_pairs, island_completed);
		negative_pairs.insert(pair_int(row - 1, col));
		}
		if (col + 1 <= n - 1)
		{
			island_surrounded = true;
			brd[row][col + 1] = '*';
		//	cout << "Cell at " << row << " " << col+1 << endl;
			block_2x2_stream(brd, pair_int(row, col+1), map_pairs, island_completed);
			negative_pairs.insert(pair_int(row, col+1));
			
		}
			
		if (col - 1 >= 0)
		{
			island_surrounded = true;
			brd[row][col - 1] = '*';
			//cout << "Cell at " << row << " " << col-1 << endl;
			block_2x2_stream(brd, pair_int(row, col-1), map_pairs, island_completed);
			negative_pairs.insert(pair_int(row, col - 1));
		}
			

		if (island_surrounded)
			island_completed[cell] = true;

	}


}

void NurikabePuzzleSolver::printFinalConfig(Node<board_conf> * node)
{
	ummarked_cells(node->nodeData.config);
	//cout << "Print Final" << endl;
	vector<board> vec_brd;
	path = false;
	if (path){
	while (node != nullptr)
	{
		//cout << "Printing path" << endl;
		vec_brd.push_back(node->nodeData.config);
		//print_board(node->nodeData.config);
		//cout << "\n\n";
		node = node->parent;
	}

	reverse(vec_brd.begin(), vec_brd.end());
	for (auto each : initial_steps)
	{
		print_board(*each);
		cout << "\n\n";
	}
	for (auto each : vec_brd)
	{
		print_board(each);
		cout << "\n\n";
	}
	}
	else
	{
		print_board(node->nodeData.config);
	}
	
	
	

}

bool adjacent_rule(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
{

	
	set_of_pair& negative_pairs = map_pairs.at("negative_cells");
	int m = brd.size();
	int n = brd[0].size();
	bool any_changes_done = false;
	const set_of_pair& pairs = map_pairs.at("positive_cells");
	
	
	for (auto cell : pairs)
	{
		int row = cell.first;
		int col = cell.second;
		
		if (row + 2 <= m - 1 && brd[row + 2][col] > 48 && brd[row + 2][col] < 58 && brd[row + 1][col] != '*')
		{
			if (brd[row + 1][col] == '-')
			{
			
			brd[row + 1][col] = '*';
			block_2x2_stream(brd, pair_int(row + 1, col), map_pairs, island_completed);
			any_changes_done = true;
			negative_pairs.insert(pair_int(row + 1,col));
			}
		}
			

		if (row - 2 >= 0 && brd[row - 2][col] > 48 && brd[row - 2][col]<58 && brd[row - 1][col] != '*')
		{
			if (brd[row - 1][col] == '-')
			{
			
			brd[row - 1][col] = '*';
			block_2x2_stream(brd, pair_int(row - 1, col), map_pairs, island_completed);
			any_changes_done = true;
			negative_pairs.insert(pair_int(row - 1, col));
		}
		}
			

		if (col + 2 <= n - 1 && brd[row][col + 2] > 48 && brd[row][col + 2]<58 && brd[row][col + 1] != '*')
		{
			if (brd[row][col + 1] == '-')
			{
			
			brd[row][col + 1] = '*';
			block_2x2_stream(brd, pair_int(row, col+1), map_pairs, island_completed);
			any_changes_done = true;
			negative_pairs.insert(pair_int(row, col + 1));
		}
		}


		if (col - 2 >= 0 && brd[row][col - 2]>48 && brd[row][col - 2] < 58 && brd[row][col - 1] != '*')
		{
			if (brd[row][col - 1] == '-')
			{
			
			brd[row][col - 1] = '*';
			block_2x2_stream(brd, pair_int(row, col-1), map_pairs, island_completed);
			any_changes_done = true;
			negative_pairs.insert(pair_int(row, col - 1));
		}
		}


	}
	
	//auto negative_cells = [](int x){ return (x == 42); };
	//get_cells(brd, negative_pairs, negative_cells);
	

	return any_changes_done;
}

bool diagonal_rule(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
{

	
	int m = brd.size();
	int n = brd[0].size();
	//cout << "m: " << m << "n: " << n << endl;
	bool any_changes_done = false;
	const set_of_pair& pairs = map_pairs.at("positive_cells");
	set_of_pair& negative_pairs = map_pairs.at("negative_cells");
	for (auto cell : pairs)
	{
		int row = cell.first;
		int col = cell.second;
		//cout << "Cell :" << "[" << row << "," << col << "]" << endl;
		//cout << "Checking 1" << endl;
		if (row + 1 <= m - 1 && col + 1 <= n - 1 && brd[row + 1][col + 1] > 48 && brd[row + 1][col + 1] < 58 && (brd[row][col + 1] != '*' || brd[row + 1][col] != '*'))
		{
		
			//cout << "1--Enter" << endl;
			/*if (brd[row][col + 1] == '-')
			{
				brd[row][col + 1] = '*';
				negative_pairs.insert(pair_int(row, col + 1));
				any_changes_done = true;
			}*/
			if (brd[row + 1][col] == '-')
			{

				brd[row + 1][col] = '*';
				block_2x2_stream(brd, pair_int(row + 1, col), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row + 1, col));
				any_changes_done = true;
			}
			
			
			//cout << "1--EXIT" << endl;
		}

		//cout << "Checking 2" << endl;
		if (row + 1 <= m - 1 && col - 1 >= 0 && brd[row + 1][col - 1] > 48 && brd[row + 1][col - 1] < 58 && (brd[row][col - 1] != '*' || brd[row + 1][col] != '*'))
		{
			
			//cout << "2-Enter" << endl;
			if (brd[row][col - 1] == '-')
			{
				brd[row][col - 1] = '*';
				block_2x2_stream(brd, pair_int(row, col-1), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row, col-1));
				any_changes_done = true;
			}
			
			if (brd[row + 1][col] == '-')
			{
				brd[row + 1][col] = '*';
				block_2x2_stream(brd, pair_int(row + 1, col), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row+1, col));
				any_changes_done = true;
			}
			
			
			//cout << "2-Exit" << endl;
			
		}

		//cout << "Checking 3" << endl;
		if (row - 1 >= 0 && col + 1 <= n - 1 && brd[row - 1][col + 1] > 48 && brd[row - 1][col + 1] < 58 && (brd[row - 1][col] != '*' || brd[row][col + 1] != '*'))
		{
			//cout << "3-Enter" << endl;
			if (brd[row][col + 1] == '-')
			{
				brd[row][col + 1] = '*';
				block_2x2_stream(brd, pair_int(row, col+1), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row, col + 1));
				any_changes_done = true;
			}
			
			if (brd[row - 1][col] == '-')
			{
				brd[row - 1][col] = '*';
				block_2x2_stream(brd, pair_int(row - 1, col), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row - 1, col));
				any_changes_done = true;
			}
			
			
			//cout << "3-Exit" << endl;

		}


		//cout << "Checking 4" << endl;
		if (row - 1 >= 0 && col - 1 >= 0 && brd[row - 1][col - 1] > 48 && brd[row - 1][col - 1] < 58 && (brd[row - 1][col] != '*' || brd[row][col - 1] != '*'))
		{
			//cout << "4-Enter" << endl;
			if (brd[row][col - 1] == '-')
			{
				brd[row][col - 1] = '*';
				block_2x2_stream(brd, pair_int(row, col-1), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row, col - 1));
				any_changes_done = true;
			}
			
			if (brd[row - 1][col] == '-')
			{
				brd[row - 1][col] = '*';
				block_2x2_stream(brd, pair_int(row - 1, col), map_pairs, island_completed);
				negative_pairs.insert(pair_int(row - 1, col));
				any_changes_done = true;
			}
			
			
			//cout << "4-Exit" << endl;
			
		}

	}

	
	return any_changes_done;

}

bool isolated_negative_cells_rule(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
{

	//cout << "isolated_negative_cells_rule-- begin" << endl;
	//print_board(brd);
	
	

	bool any_changes_done = false;
	int m = brd.size();
	int n = brd[0].size();
	
	 set_of_pair& pairs = map_pairs.at("negative_cells");

	queue<pair<int,int>> negative_neighbours;
	pair_int cell_to_extend;
	auto negative_cell_check = [&brd, &cell_to_extend](pair_int cell, int m, int n, queue<pair_int> & negative_neighbour_cells)->int
	{
		int row = cell.first;
		int col = cell.second;
		int outlet = 0;
		if (row + 1 <= m - 1)
		{
			if (brd[row + 1][col] == '-')
			{
				outlet++;
				cell_to_extend = pair_int(row + 1, col);
			}
			if (brd[row + 1][col] == '*')
			{
				negative_neighbour_cells.push(pair_int(row + 1, col));

			}

		}
		if (row - 1 >= 0)
		{
			if (brd[row - 1][col] == '-')
			{
				outlet++;
				cell_to_extend = pair_int(row - 1, col);
			}
			if (brd[row - 1][col] == '*')
			{
				negative_neighbour_cells.push(pair_int(row - 1, col));
			}


		}


		if (col + 1 <= n - 1)
		{
			if (brd[row][col + 1] == '-')
			{
				outlet++;
				cell_to_extend = pair_int(row, col + 1);
			}
			if (brd[row][col + 1] == '*')
			{
				negative_neighbour_cells.push(pair_int(row, col + 1));
			}


		}

		if (col - 1 >= 0)
		{
			if (brd[row][col - 1] == '-')
			{
				outlet++;
				cell_to_extend = pair_int(row, col - 1);

			}
			if (brd[row][col - 1] == '*')
			{
				negative_neighbour_cells.push(pair_int(row, col - 1));
			}


		}

		return outlet;
	};

	set_of_pair temp_set;
	set_of_pair dupes;
	bool print_it = false;
	for (auto cell : pairs)
	{
		dupes.insert(cell);
		//if (cell == pair_int(3, 4))
			//print_it = true;

		int outlet = negative_cell_check(cell, m, n, negative_neighbours);

		if (print_it)
		{
			cout << "outlet " << outlet << endl;
			cout <<"Size of negative neighbours "<<negative_neighbours.size() << endl;
		}
			
		

		if (outlet == 1)
		{
			
			if (negative_neighbours.empty())
			{
				
				brd[cell_to_extend.first][cell_to_extend.second] = '*';
				block_2x2_stream(brd, cell_to_extend, map_pairs, island_completed);
				any_changes_done = true;
				temp_set.insert(cell_to_extend);
			}

			else
			{
				int outlet_n = 0;
				bool neightbour_has_outlet = false;
				
					
				while(!negative_neighbours.empty())
				{
					queue<pair<int,int>> temp;
					pair_int neighbour = negative_neighbours.front();
					if (print_it)
						cout << "Exploring neighbour" << neighbour << endl;
					dupes.insert(neighbour);
					negative_neighbours.pop();
					outlet_n = negative_cell_check(neighbour, m, n, temp);
					if (print_it)
					{
						cout << "Neighbours neighbour size" << temp.size() << endl;
						cout << "Neighbours neighbour outlet" << outlet_n << endl;

					}
						
					while (!temp.empty())
					{
						

						pair_int temp_entry = temp.front();
						if (print_it)
							cout << "Neighbours neighbour" << temp_entry << endl;
						temp.pop();
						if (dupes.find(temp_entry) == dupes.end())
							negative_neighbours.push(temp_entry);
						
					}
					
						

					if (outlet_n == 0)
					{
						if (print_it)
						{
							cout << "Continuing" << endl;
							cout << "negative_neighbours size" << negative_neighbours.size() << endl;
						}
						
						continue;
						
					}
						
					
					else
					{
						neightbour_has_outlet = true;
						if (print_it)
						//cout << "Breaking" << endl;

						break;
					}

					//while (!temp.empty())
						//temp.pop();
				}
				if (!neightbour_has_outlet)
				{
					brd[cell_to_extend.first][cell_to_extend.second] = '*';
					block_2x2_stream(brd, cell_to_extend, map_pairs, island_completed);
	
					any_changes_done = true;
					temp_set.insert(cell_to_extend);
				}
					
			}

		}
		
		while (!negative_neighbours.empty())
			negative_neighbours.pop();

		print_it = false;
		dupes.clear();
	}

	for (auto each : temp_set)
		pairs.insert(each);




	//cout << "isolated_negative_cells_rule-- end" << endl;
	//print_board(brd);
	return any_changes_done;
}

void write_output(const board& brd, string file_name)
{


		fstream output(file_name, fstream::out);

	int i = 0;
	int j = 0;
	for (auto v : brd)
	{
		j = 0;
		for (auto x : v)
		{
			output << x;
			j++;
		}
		i++;
		output << endl;

		

	}
	output.close();
}

bool isolated_positive_cells_rule(board &brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int,int>,bool>& island_completed)
	{



	//cout << "isolated_positive_cells_rule--begin " << endl;
	//print_board(brd);
	//cout << "\n\n";
		bool any_changes_done = false;
		int m = brd.size();
		int n = brd[0].size();
		int positive_cell_outlet = 0;
		pair_int cell_modified;
		set_of_pair temp_set;
		set_of_pair& pairs = map_pairs.at("positive_cells");
		//cout << "Positive cells" << pairs.size() << endl;
		for (auto cell : pairs)
		{
			int row = cell.first;
			int col = cell.second;
			
			if (row + 1 <= m - 1)
			{
				if (brd[row + 1][col] == '-')
				{

					positive_cell_outlet++;
					cell_modified = pair_int(row + 1, col);
				}
			}

			if (row - 1 >= 0)
			{
				if (brd[row - 1][col] == '-')
				{

					positive_cell_outlet++;
					cell_modified = pair_int(row - 1, col);
				}
			}

			if (col + 1 <= n - 1)
			{
				if (brd[row][col + 1] == '-')
				{

					positive_cell_outlet++;
					cell_modified = pair_int(row, col + 1);
				}
			}

			if (col - 1 >= 0)
			{
				if (brd[row][col - 1] == '-')
				{

					positive_cell_outlet++;
					cell_modified = pair_int(row, col - 1);

				}
			}
			
			if (positive_cell_outlet == 1)
			{
				brd[cell_modified.first][cell_modified.second] = '?';
				any_changes_done = true;
				if(!isolate_island_if_completed(brd,cell_modified, map_pairs,island_completed))
				temp_set.insert(cell_modified);
			}
				
			positive_cell_outlet = 0;
			cell_modified = pair_int();
		}

		for (auto each:temp_set)
		pairs.insert(each);

		//print_board(brd);
		//cout << "isolated_positive_cells_rule --end" << endl;
		

		return any_changes_done;
	}
	
bool isolate_island_if_completed(board& brd, const pair_int cell, unordered_map<string, set_of_pair>& map_pairs,map<pair<int, int>, bool> &completed_islands)
	{

		
	
	int m = brd.size();
		int n = brd[0].size();
		int row, col;
		set<pair_int>set_of_cells_path;
		set_of_cells_path.insert(cell);
		int limit=0;
		auto is_it_number = [](const char ch){return (ch > 48 && ch < 58); };
		if (is_it_number(brd[cell.first][cell.second]))
			limit = ((brd[cell.first][cell.second]) - 48);
		queue<pair_int> island;
		island.push(cell);
		pair_int temp_cell;
		pair_int add_cell;
		pair_int cell_containing_number;
		while (!island.empty())
		{
			temp_cell = island.front();
			island.pop();
			row = temp_cell.first;
			col = temp_cell.second;

			

			if (row + 1 <= m - 1)
			{

				

				if (set_of_cells_path.find(pair_int(row + 1, col)) == set_of_cells_path.end() && brd[row + 1][col] == '?' || is_it_number(brd[row + 1][col]))
				{
					
					add_cell = pair_int(row + 1, col);
					if (is_it_number(brd[add_cell.first][add_cell.second]))
					{
						limit = ((brd[add_cell.first][add_cell.second]) - 48);
						cell_containing_number = add_cell;
					}
						
					set_of_cells_path.insert(add_cell);
					island.push(add_cell);
				}
			}
						
			
			if (row - 1 >= 0)
			{
				
				//cout << "Checking neighbour : [" << row - 1 << "," << col << "]" << endl;
				if (set_of_cells_path.find(pair_int(row - 1, col)) == set_of_cells_path.end() && brd[row - 1][col] == '?' || is_it_number(brd[row - 1][col]))
				{
					//cout << "Contains positive " << endl;
					add_cell = pair_int(row - 1, col);
					if (is_it_number(brd[add_cell.first][add_cell.second]))
					{
						limit = ((brd[add_cell.first][add_cell.second]) - 48);
						cell_containing_number = add_cell;
					}
						
					set_of_cells_path.insert(add_cell);
					island.push(add_cell);
				}
			}
			
			
			
			if (col + 1 <= n - 1)
			{
				//cout << "Checking neighbour : [" << row << "," << col+1 << "]" << endl;
				if (set_of_cells_path.find(pair_int(row, col+1)) == set_of_cells_path.end() && brd[row][col+1] == '?' || is_it_number(brd[row][col+1]))
				{
					//cout << "Contains positive " << endl;
					add_cell = pair_int(row, col+1);
					if (is_it_number(brd[add_cell.first][add_cell.second]))
					{
						cell_containing_number = add_cell;
						limit = ((brd[add_cell.first][add_cell.second]) - 48);
					}
						
					set_of_cells_path.insert(add_cell);
					island.push(add_cell);
				}
			}
			


			if (col - 1 >= 0)
			{
				//cout << "Checking neighbour : [" << row<< "," << col-1 << "]" << endl;
				if (set_of_cells_path.find(pair_int(row, col - 1)) == set_of_cells_path.end() && brd[row][col - 1] == '?' || is_it_number(brd[row][col - 1]))
				{
					//cout << "Contains positive " << endl;
					add_cell = pair_int(row, col - 1);
					if (is_it_number(brd[add_cell.first][add_cell.second]))
					{
						limit = ((brd[add_cell.first][add_cell.second]) - 48);
						cell_containing_number = add_cell;
					}
						
					set_of_cells_path.insert(add_cell);
					island.push(add_cell);

						
				}

				
				
			}
			

		}

		bool any_island_completed = (set_of_cells_path.size() == limit);
		if (any_island_completed)
		{
			isolate_island(brd,map_pairs,completed_islands, set_of_cells_path);
			completed_islands[cell_containing_number] = true;

		}
			
		return any_island_completed;
	}
	
	void isolate_island(board& brd, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed,const set<pair_int> island)
	{
		int m = brd.size();
		int n = brd[0].size();
		int row, col;

		for (auto cell : island)
		{
			//cout << "Examining cell " << "[" << cell.first << "," << cell.second << "]" << endl;
			row = cell.first;
			col = cell.second;

			if (row + 1 <= m - 1 && (island.find(pair<int, int>(row + 1, col)) == island.end()))
			{
				//cout << "Changing" << "[" << row + 1 << "," << col << "]" << endl;
				if (brd[row + 1][col] != '*')
				{

					brd[row + 1][col] = '*';
					block_2x2_stream(brd, pair_int(row + 1, col), map_pairs, island_completed);
				}
			}
			if (row - 1 >= 0 && (island.find(pair_int(row - 1, col)) == island.end()))
			{
				//cout << "Changing" << "[" << row - 1 << "," << col << "]" << endl;
				if (brd[row - 1][col] != '*')
				{

					brd[row - 1][col] = '*';
					block_2x2_stream(brd, pair_int(row - 1, col), map_pairs, island_completed);
				}
			}
			if (col + 1 <= n - 1 && (island.find(pair_int(row, col + 1)) == island.end()))
			{
				//cout << "Changing" << "[" << row  << "," << col+1 << "]" << endl;
				if (brd[row][col + 1] != '*'){
				brd[row][col + 1] = '*';
				block_2x2_stream(brd, pair_int(row, col + 1), map_pairs, island_completed);
			}
		}
		if (col - 1 >= 0 && (island.find(pair_int(row, col - 1)) == island.end()))
		{
			//cout << "Changing" << "[" << row << "," << col-1 << "]" << endl;
			if (brd[row][col - 1] != '*')
			{
				brd[row][col - 1] = '*';
				block_2x2_stream(brd, pair_int(row, col - 1), map_pairs, island_completed);
			}
		}
		}

		

	}
	
	


	bool block_2x2_stream(board& brd, pair<int,int> cell, unordered_map<string, set_of_pair>& map_pairs, map<pair<int, int>, bool>& island_completed)
	{
		
		int m = brd.size();
		int n = brd[0].size();

		vector<pair_int> neighbours;
		vector<pair_int> diagonal_neighbours;
		set_of_pair& pairs = map_pairs.at("positive_cells");
		vector<pair_of_pair> combos;
		int row = cell.first;
		int col = cell.second;
		bool any_changes_done = false;
		set_of_pair temp_set;
		
		
		if (row + 1 <= m - 1)
		{
			if (brd[row + 1][col] == '*')
				neighbours.push_back(pair_int(row + 1, col));
		}

		if (row - 1 >= 0)
		{
			if (brd[row - 1][col] == '*')
				neighbours.push_back(pair_int(row - 1, col));
		}

		if (col + 1 <= n - 1)
		{
			if (brd[row][col + 1] == '*')
				neighbours.push_back(pair_int(row, col + 1));
		}
		if (col - 1 >= 0)
		{
			if (brd[row][col - 1] == '*')
				neighbours.push_back(pair_int(row, col - 1));
		}

		if (row + 1 <= m - 1 && col + 1 <= n - 1)
		{
			if (brd[row + 1][col + 1] == '*')
				diagonal_neighbours.push_back(pair_int(row + 1, col + 1));

		}
		if (row + 1 <= m - 1 && col - 1 >= 0)
		{
			if (brd[row + 1][col - 1] == '*')
				diagonal_neighbours.push_back(pair_int(row + 1, col - 1));

		}

		if (row - 1 >= 0 && col + 1 <= n - 1)
		{
			if (brd[row - 1][col + 1] == '*')
				diagonal_neighbours.push_back(pair_int(row - 1, col + 1));

		}

		if (row - 1 >= 0 && col - 1 >= 0)
		{
			if (brd[row - 1][col - 1] == '*')
				diagonal_neighbours.push_back(pair_int(row - 1, col - 1));

		}



		//cout << "Neighbours are" << endl;
		for (int i = 0; i < neighbours.size(); i++)
		for (int j = i + 1; j < neighbours.size(); j++)
		{
			pair_int g1 = neighbours[i];
			pair_int g2 = neighbours[j];
			if ((g1.first != g2.first) && (g1.second != g2.second))
				combos.push_back(pair_of_pair(neighbours[i], neighbours[j]));
		}

		//cout << "Neighbours " << neighbours.size() << endl;
		//cout << "Combos size " << combos.size() << endl;

		for (auto z : combos)
		{
			pair_int neighbour1 = z.first;
			pair_int neighbour2 = z.second;
			int x, y;
			if (neighbour1.first != cell.first)
				x = neighbour1.first;
			else
				x = neighbour2.first;


			if (neighbour1.second != cell.second)
				y = neighbour1.second;

			else
				y = neighbour2.second;

			if (brd[x][y] == '-')
			{
				brd[x][y] = '?';
				any_changes_done = true;
				if (!isolate_island_if_completed(brd, pair_int(x,y), map_pairs,island_completed))
					temp_set.insert(pair_int(x, y));
			}
				
		}



		for (auto z : diagonal_neighbours)
		{
			int diag_x = z.first;
			int diag_y = z.second;
			int cell_x = cell.first;
			int cell_y = cell.second;

			if (brd[diag_x][cell_y] == '*')
			{
				if (brd[cell_x][diag_y] == '-')
					brd[cell_x][diag_y] = '?';
				any_changes_done = true;
		if (!isolate_island_if_completed(brd, pair_int(cell_x, diag_y),map_pairs, island_completed))
				temp_set.insert(pair_int(cell_x, diag_y));


			}

			if (brd[cell_x][diag_y] == '*')
			{
				if (brd[diag_x][cell_y] == '-')
					brd[diag_x][cell_y] = '?';
				any_changes_done = true;
				if (!isolate_island_if_completed(brd, pair_int(diag_x, cell_y), map_pairs, island_completed))
				temp_set.insert(pair_int(diag_x, cell_y));

			}

		}


		for (auto each : temp_set)
			pairs.insert(each);
					
		return any_changes_done;

	}






void readInput(const string& filename,board &board_ptr)
{
	ifstream inputFile;
	string inputLine;
	vector<char> vec;
	int i = 0;
	int j = 0;
	inputFile.open(filename, ios::in);
	//getline(inputFile, inputLine);
	while (!inputFile.eof()) {
		i++;
		getline(inputFile, inputLine);
		//cout << "Line" << inputLine<<endl;
		j = 0;
		for (auto each : inputLine)
		{
			//cout << "char is " << (int)each << endl;
			if (each != 13)
			{
				j++;
				vec.push_back(each);
			}
			
		}
		//vec.pop_back();
		board_ptr.push_back(vec);
		//board_ptr.erase(board_ptr.size() - 1);
		//cout << "vec size is " << vec.size() << endl;
		//cout << "j is " << j << endl;
		//cout << "inputLine" << inputLine.length() << endl;
		
		vec.clear();


	}
	//cout << "i is " << i << endl;
	//board_ptr.pop_back();

	/*ifstream input_stream(filename);
	char cell;
	vector<char> temp_row = vector<char>();
	int i = 0;
	while (!input_stream.eof())
	{
		i++;
		cell = input_stream.get();
		if (cell == '\n')
		{
			board_ptr.push_back(temp_row);
			temp_row = vector<char>();
		}
		else
		temp_row.push_back(cell);
	}
	board_ptr.push_back(temp_row);
	//cout << "Total size" << i << endl;*/
	

	inputFile.close();




}

void print_board(board brd)

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




/*
int main(int argc,char* argv[])
{
	
	shared_ptr<board_conf> board_ptr = make_shared<board_conf>();
	string filename;
	bool path=false;
	//cout << "Argumrnts" << argc << endl;
	if (argc == 3){
		filename = argv[2];
		
		path = (string(argv[1]) == "path");
	}
	else if (argc == 2)
	{
		filename = argv[1];
	}
	//cout << "Filename is " << filename;
	readInput(filename, board_ptr->config);
	print_board(board_ptr->config);
	//cout << "\n\n";
	unordered_map<string, set_of_pair> map_pairs;
	set_of_pair temp_set;
	temp_set.insert(pair<int,int>(2,2));
	map_pairs.insert(pair<string, set_of_pair>("positive_cells", temp_set));
	map<pair_int, bool> islands_completed;
	//block_2x2_stream(*board_ptr,pair_int(2,3),map_pairs, islands_completed);
	//print_board(*board_ptr);
	NurikabePuzzleSolver *p = new NurikabePuzzleSolver(*board_ptr, path);
	
	p->solve();
	delete p;
	//print_board(*board_ptr);
	//write_output(*board_ptr,"out0.txt");

	//shared_ptr<cell> paren = make_shared<cell>(nullptr, 1, pair<int, int>(1,3));
	//shared_ptr<cell> child = make_shared<cell>(paren.get(), 2, pair<int, int>(1, 4));

	//cout << "" << (child->parent->parent==nullptr) << endl;
	system("PAUSE");
	return 0;
}


*/

