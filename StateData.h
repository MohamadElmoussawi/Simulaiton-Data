#pragma once
#include <iostream>
using namespace std;
struct StateData{
	StateData(){
		_num_dem_wins = 0;
		_num_rep_wins = 0;
		_num_ties = 0;
	}
	StateData(string name, int electoral, double republican, double democrat);
	//States name
	string _name;
	//Number of electoral votes
	int _electoral;
	//Percentage of popular vote going towards republican candidate
	double _republican;
	//Percentage of popular vote going towards democratic candidate
	double _democrat;
	int _num_dem_wins;
	int _num_rep_wins;
	int _num_ties;
	void print_me();
};

