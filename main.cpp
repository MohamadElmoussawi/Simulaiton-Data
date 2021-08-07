#include <fstream>
#include <algorithm> 
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "CONSTANTS.h"
#include "StateData.h"
using namespace std;
double get_random_error();
void print_state_data(vector<StateData>& states);
void run_simulation(vector<StateData>& states, int& num_rep_votes,
    int& num_dem_votes, int& num_tied_electoral);
int main() {
    string name,electoral,republican,democrat;
    ifstream poll_data("data.csv");
    ofstream demresults;
    ofstream represults;
    represults.open("represults.txt");
    demresults.open("demresults.txt");
    vector<StateData> states;
    StateData temp;
    int count = 1;
    while (!poll_data.eof()) {
        getline(poll_data, name, ',');
        getline(poll_data, electoral, ',');
        getline(poll_data, republican, ',');
        getline(poll_data, democrat);
        temp._name = name;
        temp._electoral = stoi(electoral);
        temp._republican = stod(republican);
        temp._democrat = stod(democrat);
        states.push_back(temp);
    }
    int total_dem = 0, total_rep = 0, total_tied = 0;
    for(int i =0; i < NUM_SIMS;i++){
        int dem, rep, tied;
        run_simulation(states, rep, dem, tied);
        demresults << dem << endl;
        represults << rep << endl;
        if (dem > 270) {
            total_dem++;
        }
        else if (rep > 270) {
            total_rep++;
        }
        else {
            total_tied++;
        }
    }
    cout << "Percentage of Trump wins: " << (double(total_rep) / NUM_SIMS) * 100 << endl;
    cout << "Percentage of Biden wins: " << (double(total_dem) / NUM_SIMS) * 100 << endl;
    cout << "Tie percentage: " << (double(total_tied) / NUM_SIMS) * 100 << endl;
    represults.close();
    demresults.close();
    poll_data.close();
    print_state_data(states);
}
void run_simulation(vector<StateData>& states, int& num_rep_votes, 
    int& num_dem_votes,int& num_tied_electoral) {
    num_dem_votes = 0;
    num_rep_votes = 0;
    num_tied_electoral = 0;
    double adjusted_republican;
    double adjusted_democrat;
    for (int i = 0; i < states.size(); i++) {
        adjusted_republican = states[i]._republican + get_random_error();
        adjusted_democrat = states[i]._democrat  + get_random_error();
        if (adjusted_democrat > adjusted_republican) {
            num_dem_votes += states[i]._electoral;
            states[i]._num_dem_wins++;
        }
        else if (adjusted_democrat < adjusted_republican) {
            num_rep_votes += states[i]._electoral;
            states[i]._num_rep_wins++;
        }
        else {
            num_tied_electoral += states[i]._electoral;
            states[i]._num_ties++;
        }
    }
}
double get_random_error() {
    //Setup
    random_device randomness_device{};
    mt19937 pseudorandom_generator{ randomness_device() };
    normal_distribution<> distribution{ mean, std_dev };
    double sample = distribution(pseudorandom_generator);
    double clamped = std::max(min_allowed, std::min(sample, max_allowed));
    return clamped;
}
void print_state_data(vector<StateData>& states) {
    for (int i = 0; i < states.size(); i++) {
        cout << states[i]._name << " Dem Winrate: " 
            << (double(states[i]._num_dem_wins) / NUM_SIMS) * 100;
        cout << " Rep Winrate: "
            << (double(states[i]._num_rep_wins) / NUM_SIMS) * 100 << endl;
    }
}