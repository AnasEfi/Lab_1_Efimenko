#include "NetWork.h"

NetWork::NetWork()
{
	ExistNetwork = false;
	
}

void NetWork::Print(unordered_set <int> s) {
    for (auto& x : s) {
        cout << x << " ";
    }
}
bool NetWork::checkAvailablePipe(const unordered_map <int, Pipe>& mPipe) {
    bool p = false;
    for (auto& item : mPipe) {
        if (item.second.GetIN() == -1)
            p = true;
    }
    return p;
}
void NetWork::PrintS(const unordered_map <int, int>& m) {
    for (auto& i : m) {
        cout << i.first << i.second << endl;
    }
}
void NetWork::ConnectPipes(unordered_map <int, Pipe>& mPipe, unordered_map <int, compressorStation>& mStation) {
    int InID = -1;
    int OutID = -1;
    int PipeID = -1;

    auto result = FindbyFilter(mPipe, Checkbystatus, false);
    int inwork = result.size();
    if (checkAvailablePipe(mPipe) == false || mStation.size() <= 1 || mPipe.size() == 0 || inwork == 0) {
        cout << "нет доступных труб или станций" << endl;
        return ;
    }
    else {
        cout << "соединить КС [ID]: ";
        OutID = SelectItem(mStation).GetID();
        cout << "c КС [ID]: ";
        while (true) {
            InID = SelectItem(mStation).GetID();
            if (InID == OutID)
                cout << "Цех начала трубы,введите другой: ";
            else break;
        }
        cout << "трубой [ID]: ";
        do {
            PipeID = SelectItem(mPipe).GetID();
            if ((mPipe[PipeID].GetUsed() == true)) 
            {
                cout << "Труба уже использована, другое ID: ";
            }
        } while ((mPipe[PipeID].GetStatus() == true) || (mPipe[PipeID].GetIN() != -1) || (mPipe[PipeID].Getout() != -1));

        for (auto& it : mPipe) {
            if ((it.second.GetIN() == OutID) && (it.second.Getout() == InID))
            {
                cout << "Cтанции уже соединены" << endl; 
                mPipe[PipeID].SetUsed(false);
                return;
            }
        }
        mPipe[PipeID].SetUsed(true);
        mPipe.find(PipeID)->second.SetIN(InID);
        mPipe.find(PipeID)->second.SetOUT(OutID);
        
        return;
    }
}
void NetWork::Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation)
{
    involved_Pipes.clear();
    involved_Stations.clear();
    position_station.clear();
    position_station_invert.clear();

    for (auto& item : mPipe) {
        if ((item.second.GetIN() != -1) && (item.second.Getout() != -1)) {
            involved_Pipes.insert(item.first);
            involved_Stations.insert(item.second.GetIN());
            involved_Stations.insert(item.second.Getout());
        }
        if ((item.second.GetStatus() == 0) && (item.second.GetIN() != -1))
            involved_Stations.insert(item.second.GetIN());
        if ((item.second.GetStatus() == 0) && (item.second.Getout() != -1))
            involved_Stations.insert(item.second.Getout());
    }
        int k = 0;
        for (auto i : involved_Stations) {
            position_station.emplace(i, k);
            ++k;
        }
        int d = 0;
        for (auto i : involved_Stations) {
            position_station_invert.emplace(d, i);
            ++d;
        }
        int x = involved_Stations.size();
        int amount_of_picks = x;
        int val = 0;
        for (int i = 0; i < x; i++)
        {
            matrix.push_back(vector<double>());
            for (int j = 0; j < x; j++)
            {
                matrix.back().push_back(val);
            }
        }
        int indexi, indexj;
        for (auto k : involved_Pipes) {
            for (auto item : mPipe) {
                if (k == item.first) {
                    indexi = position_station[item.second.Getout()];
                    indexj = position_station[item.second.GetIN()];
                    (item.second.GetStatus()) ? matrix[indexi][indexj] = 0 : matrix[indexi][indexj] = item.second.GetWeight();
                    break;
                }
            }
        }
        ViewNetwork(matrix, involved_Stations);
        double sum = 0;
        unordered_set<int>sort;
        vector <int> visit(x, 0);
        for (int i = 0; i < x; i++)
            if (cycle(i, matrix, visit)) {
                cout << "В графе есть цикл" << endl;
                return;
            }

        do {
            for (int j = 0; j < x; j++) {
                for (int i = 0;i < x;i++) {
                    sum = sum + matrix[i][j];
                }
                if (sum == 0) {
                    sort.insert(j);
                    for (int i = 0; i < x; i++) {
                        if (matrix[j][i] != 0) {
                            sort.insert(i);
                            matrix[j][i] = 0;
                        }
                    }
                }
            }
        } while (sort.size() != involved_Stations.size());

        for (int i = 0;i < x; i++) {
            for (int j = 0;j < x;j++) {
                if (matrix[i][j] != 0) {

                }
            }
        }
        if (sort.size() == 0) {
            cout << "Нет связей для графа" << endl;
            return;
        }
        cout << "Топологическая сортировка" << endl;
        for (auto& i : sort) {
            if (position_station_invert.find(i) != position_station_invert.end())
                cout << position_station_invert.find(i)->second<<" ";
        }
}

bool NetWork::cycle(int start,vector <vector <double>> g, vector <int>& visit)
{
    visit[start] = 1; 
    for (unsigned int j = 0; j < g[start].size(); j++)
        if (g[start][j] != 0) {
            if (visit[j] == 0) {
                if (cycle(j, g, visit)) return true;
            }
            else if (visit[j] == 1)
                return true;
        }
    visit[start] = 2; 
    return false;
}

void NetWork::ViewNetwork(const vector<vector<double>>& graph, const set<int>& involved_Stations)
{
    set<int>::iterator it;
    it = involved_Stations.begin();
    cout << setw(7) << "*";
    for (int i = 0; i < involved_Stations.size(); i++) {
        cout << setw(7) << *it;
        it++;
    }
    cout << endl;
    it = involved_Stations.begin();
    for (unsigned int i = 0; i < involved_Stations.size(); i++)
    {
        cout << setw(7) << *it;
        it++;
        for (unsigned int j = 0; j < involved_Stations.size(); j++)
            cout << setw(7) << graph[i][j];
        cout << endl;
    }
}
