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
	unordered_set<int> Topological_Sort(NetWork& Current_Network);
	void BFS(const NetWork& Current_Network, int start,int end);
	void ConnectPipes(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation);
	bool cycle(int start, vector <vector <double>>& g, vector <int>& visit);
	double max_flow(const NetWork& current_Network, int s, int t);
	void ViewNetwork(const std::vector<std::vector<double>>& graph, const std::set<int>& Station_Connection);
	void Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation, NetWork& Current_Network);
	bool checkAvailablePipe(const unordered_map<int, Pipe>& mPipe);
	vector<vector<double>> GetMatrix() const;
	vector<vector<double>> GetMatrix2() const;
	set<int> GetPipes() const;
	set<int> GetStations()const;
	void SetmatrixL(vector<vector<double>> new_matrix);
	void SetmatrixW(vector<vector<double>> new_matrix);
	unordered_map <int, int> GetPosition() const;

};
template <typename Type>
Type& SelectItem(unordered_map <int, Type>& m);
template<typename Type, typename T>
vector <int> FindbyFilter(const unordered_map <int, Type>& group, Filter <Type, T> f, T parameter);
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter);


