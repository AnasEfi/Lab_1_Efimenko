#pragma once
#include <set>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>
#include "utils.h"
#include "CStation.h"
#include "CPipe.h"

class NetWork
{
private:
	vector<vector<double>> matrix;
	vector<vector<double>> matrix2;
	vector<int> used;
	vector<int> ans;
	set<int> involved_Pipes;
	set<int> involved_Stations;
	unordered_map <int, int> position_station;
	unordered_map <int, int> position_station_invert;
	unordered_map<int, int> connection_between_Stations;
	bool ExistNetwork;
public:
	
	NetWork();
	void Topological_Sort(NetWork& Current_Network);
	void Dextra(const NetWork& Current_Network, int start,int end);
	void ConnectPipes(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
	bool cycle(int start, vector <vector <double>>& g, vector <int>& visit);
	double max_flow(const NetWork& current_Network, int s, int t);
	void ViewNetwork(const NetWork& CurrentNetwork);
	void Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation, NetWork& Current_Network);
	int SelectItemFromGraph(const set<int>& m);
	bool checkAvailablePipe(const unordered_map<int, Pipe>& mPipe);

	bool GetExistion() const;
	set<int> GetPipes() const;
	set<int> GetStations()const;
	unordered_map <int, int> GetPosition() const;
};
template <typename Type>
Type& SelectItem(unordered_map <int, Type>& m);
template<typename Type, typename T>
vector <int> FindbyFilter(const unordered_map <int, Type>& group, Filter <Type, T> f, T parameter);
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter);
