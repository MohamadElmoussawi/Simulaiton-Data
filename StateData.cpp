#include "StateData.h"
StateData::StateData(string name, int electoral, double republican, double democrat) {
	_name = name;
	_electoral = electoral;
	_republican = republican;
	_democrat = democrat;
	_num_dem_wins = 0;
	_num_rep_wins = 0;
	_num_ties = 0;
}
void StateData::print_me(){
	cout << "State Name: " << _name << " Electoral Votes " << _electoral
		<< " Republican Percentage " << _republican
		<< " Democrat Percentage " << _democrat;
}