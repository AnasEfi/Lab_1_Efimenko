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
   bool p = true;
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
            mPipe[PipeID].SetUsed(true);
            if ((mPipe[PipeID].GetUsed() == true)) cout << "Труба уже использована, другое ID: ";
            if (mPipe[PipeID].GetIN() == (InID || OutID) && mPipe[PipeID].Getout() == (InID || OutID)) {
                cout << "Cтанции уже соединены" << endl;  p = false;
            }
        }
        while ((mPipe[PipeID].GetStatus() == true)||(mPipe[PipeID].GetIN()!=-1)|| (mPipe[PipeID].Getout() != -1)||p==false);
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
        if ((item.second.GetStatus() == 0) && (item.second.GetIN() != -1) && (item.second.Getout() != -1)) {
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
        //PrintS(position_station);
        //PrintS(position_station_invert);

        int x = involved_Stations.size();
        int amount_of_picks = x;
        vector<vector<double>> matrix;

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
                    matrix[indexi][indexj] = item.second.GetWeight();
                    break;
                }
            }
        }
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < x; j++)
            {
                std::cout << matrix[i][j] << "\t";
            }
            cout << "\n";
        }
        double sum = 0;

        unordered_set<int>sort;

        std::vector <int> visit(x, 0);
        for (int i = 0; i < x; i++)
            if (cycle(i, matrix, visit)) {
                std::cout << "There is a cycle in the network" << std::endl;
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

        
       // Print(sort);
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
                cout << position_station_invert.find(i)->second;
        }
}

bool NetWork::cycle(int start, std::vector <std::vector <double>> g, std::vector <int>& visit)
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