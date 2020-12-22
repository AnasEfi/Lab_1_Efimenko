#pragma once
#include <set>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <iomanip>
#include "utils.h"
#include "CStation.h"
#include "CPipe.h"

class NetWork
{
private:
	vector<vector<double>> matrix;
	set<int> involved_Pipes;
	set<int> involved_Stations;
	unordered_map <int, int> position_station;
	unordered_map <int, int> position_station_invert;
	vector<int> used;
	bool ExistNetwork;
	vector<int> ans;
	unordered_map<int, int> connection_between_Stations;
	
public:
	
	NetWork();
	void Print(unordered_set <int> s);
	void PrintS(const unordered_map<int, int>& m);
	void ConnectPipes(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
	bool cycle(int start, std::vector <std::vector <double>> g, std::vector <int>& visit);
	void ViewNetwork(const std::vector<std::vector<double>>& graph, const std::set<int>& Station_Connection);
	void Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
	bool checkAvailablePipe(const unordered_map<int, Pipe>& mPipe);

};
template <typename Type>
Type& SelectItem(unordered_map <int, Type>& m);
template<typename Type, typename T>
vector <int> FindbyFilter(const unordered_map <int, Type>& group, Filter <Type, T> f, T parameter);
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter);


