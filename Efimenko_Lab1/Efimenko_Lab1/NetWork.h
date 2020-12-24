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
	bool ExistNetwork;
	vector<vector<double>> matrix;//path
	vector<vector<double>> matrix2;//productivity
	vector<int> used;
	vector<int> ans;
	set<int> involved_Pipes;
	set<int> involved_Stations;
	unordered_map <int, int> position_station;//for matrix
	unordered_map <int, int> position_station_invert;//for matrix
	unordered_map<int, int> connection_between_Stations;//for matrix
public:
	NetWork();

	void Topological_Sort(NetWork& Current_Network);
	void Dextra(const NetWork& Current_Network, int start,int end);
	void ConnectPipes(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
	bool cycle(int start, vector <vector <double>>& g, vector <int>& visit);
	double max_flow(const NetWork& current_Network, int s, int t);
	void ViewNetwork(int p);
	void Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
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
