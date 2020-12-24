#include "NetWork.h"
#include <queue>

NetWork::NetWork()
{
	ExistNetwork = false;
}

int NetWork::SelectItemFromGraph(const set<int>& m) {
    set<int>::iterator it;
    int id;
    while (1) {
        cout << "Введите номер: ";
        cin >> id;
        if (involved_Stations.find(id) != involved_Stations.end() && !ErrorCin(id))
            return id;
        else {
            cout << "Доступные станции: ";
            for (auto it = begin(m);it != end(m);++it) {
                if (involved_Stations.find(*it) != involved_Stations.end())
                    cout << *it << " ";
            }
        }
    }
}

bool NetWork::checkAvailablePipe(const unordered_map <int, Pipe>& mPipe) {
    bool p = false;
    for (auto& item : mPipe) {
        if (item.second.GetIN() ==-1)
            p = true;
    }
    return p;
}
bool NetWork::GetExistion() const
{
    return ExistNetwork;
}
//
//vector<vector<double>> NetWork::GetMatrix2() const
//{
//    return matrix2;
//}

set<int> NetWork::GetPipes() const
{
    return involved_Pipes;
}

set<int> NetWork::GetStations() const
{
    return involved_Stations;
}

unordered_map<int, int> NetWork::GetPosition() const
{
    return position_station;
}
//void NetWork::PrintS(const unordered_map <int, int>& m) {
//    for (auto& i : m) {
//        cout << i.first << i.second << endl;
//    }
//}

bool NetWork::cycle(int start, vector <vector <double>>& g, vector <int>& visit)
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
void NetWork::Create_Graph(unordered_map<int, Pipe>& mPipe, unordered_map<int, compressorStation>& mStation, NetWork& Current_Network)
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
    if (x == 0) {
        cout << "Невозможно построить граф" << endl;
        ExistNetwork = false;
        return;
    }
    int amount_of_picks = x;
    int val = 0;
    for (int i = 0; i < x; i++)
    {
        matrix.push_back(vector<double>());
        matrix2.push_back(vector<double>());
        for (int j = 0; j < x; j++)
        {
            matrix.back().push_back(val);
            matrix2.back().push_back(val);
        }
    }
    int indexi, indexj;
    for (auto k : involved_Pipes) {
        for (auto item : mPipe) {
            if (k == item.first) {
                indexi = position_station[item.second.Getout()];
                indexj = position_station[item.second.GetIN()];
                if (item.second.GetStatus()) {
                    matrix[indexi][indexj] = 0;
                }
                else {
                    matrix[indexi][indexj] = item.second.GetWeight();
                    matrix2[indexi][indexj] = item.second.GetWeight();
                }
                break;
            }
        }
    }
    ExistNetwork = true;
}
void NetWork::Topological_Sort(NetWork& Current_Network) {
    vector<vector<double>> matrix_for_sort;
    int N = Current_Network.GetStations().size();
    double sum = 0;
    unordered_set<int>sort;
    vector <int> visit(N, 0);
    for (int i = 0; i < N; i++)
        matrix_for_sort.push_back(vector<double>());
    matrix_for_sort = matrix;
    for (int i = 0; i < N; i++) {
        if (cycle(i, matrix_for_sort, visit)) {
            cout << "В графе есть цикл" << endl;
            return ;
        }
    }
    do {
        for (int j = 0; j < N; j++) {
            for (int i = 0;i < N;i++) {
                sum = sum + matrix_for_sort[i][j];
            }
            if (sum == 0) {
                sort.insert(j);
                for (int i = 0; i < N; i++) {
                    if (matrix_for_sort[j][i] != 0) {
                        sort.insert(i);
                        matrix_for_sort[j][i] = 0;
                    }
                }
            }
        }
    } while (sort.size() != Current_Network.GetStations().size());

    cout << "Топологическая сортировка" << endl;
    for (auto it = begin(sort);it != end(sort);++it) {
        if (position_station_invert.find(*it) != position_station_invert.end()) {
            if (it == begin(sort)) cout << position_station_invert.find(*it)->second; else
                cout << "->" << position_station_invert.find(*it)->second;
        }
    }
}

void NetWork::Dextra(const NetWork& Current_Network, int start, int endv) {
    vector<vector<double>> matrix_for_length = Current_Network.matrix;
    int s = start;              		// Номер исходной вершины
    int e = endv;              		// Номер конечной вершины
    int N = Current_Network.involved_Stations.size(), minindex, min;
    int save;//переменная для временного хранения величин
    int infinity = 10000;
    int v;
    vector <double> d;
    vector <int>a;
    vector <double>h;
    if (start == endv) {
        cout << "Путь:0";
        return;
    }
 
    for (int i = 0; i < N; i++) {
        d.push_back(10000);
        a.push_back(1);//отмечает все вершины как необработанные
    }
    d[s] = 0;
    do {
        minindex = 10000;//индекс вершины с минимальным весом
        min = 10000;// мин вес
        for (int i = 0; i < N; i++)
        {
            if ((a[i] == 1) && (d[i] < min))
            {
                min = d[i];
                minindex = i;
            }
        }
        if (minindex != 10000)
        {
            for (int i = 0; i < N; i++)
            {
                if (matrix[minindex][i] > 0)
                {
                    save = min + matrix[minindex][i];
                    if (save < d[i])
                    {
                        d[i] = save;
                    }
                }
            }
            a[minindex] = 0;
        }
    } while (minindex < 10000);
    vector<int> ver(N); // массив посещенных вершин
    ver[0] = e; // начальный элемент - последняя вершина
    int k = 0; // индекс предыдущей вершины
    double weight = d[e];
    if (weight == 10000) { cout << "Нет пути" << endl; return; }
    cout << "Длина пути: " << weight << endl;// вес последней вершины
    while (e != s) {
        for (int i = 0; i < N; i++)
            if (matrix[i][e] != 0)
            {
                int temp = weight - matrix[i][e]; // вес пути из предыдущей вершины
                if (temp == d[i])
                {
                    weight = temp;
                    e = i; // сохраняем предыдущую вершину
                    ver[k] = i; // записываем ее в массив
                    k++;
                }
            }
    }
    ver.resize(k-1);
    ver.insert(ver.begin(), start);
    ver.insert(ver.end(), endv);
    for (auto it = begin(ver);it != end(ver);++it) {
        if (position_station_invert.find(*it) != position_station_invert.end()) {
            if (it == begin(ver)) cout << position_station_invert.find(*it)->second; else
                cout << "->" << position_station_invert.find(*it)->second;
        }
    }
}


int bfs(int s, int t,int N, double MAX_VAL, vector<vector<double>>&F, vector<vector<double>>&C,vector<double>& push, vector<int>&pred)
{
    vector<int>visited(N);        // Отметки на вершинах, в которых побывали
    vector<int> dist(N);        // Расстояние до вершины [v] из начальной точки
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
        push[i] = 0;
        pred[i] = 0;
        dist[i] = MAX_VAL;
    }
    queue<int> Q;
    visited[s] = 1;
    pred[s] = s;
    push[s] = MAX_VAL;
    Q.push(s);
    while (!visited[t] && !Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int v = 0; v < N; v++)
            if (!visited[v] && (C[u][v] - F[u][v] > 0))
            {
                push[v] = min(push[u], C[u][v] - F[u][v]);
                visited[v] = 1;
                pred[v] = u;
                Q.push(v);
            }
    }
    return visited[t];
}
double NetWork::max_flow(const NetWork& current_Network, int s, int t)
{
    int max_flow;
    int u, v, flow = 0;
    double MAX_Flow=500;
    int St,P;
    St=current_Network.involved_Stations.size();//кол-во вершин
   // P = sizeof(current_Network.GetPipes());//кол-во ребер
    auto C = matrix;    // Матрица "пропускных способностей"
    size_t N = current_Network.GetStations().size();
    vector<vector<double>> F;
    F.resize(N);
    double val = 0;
    for (int i = 0; i < N; ++i) F[i].resize(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            F[i][j] = val;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << F[i][j] << " ";
        cout << "\n";
    }
        
    // Матрица "текущего потока в графе"
    //auto P = current_Network.GetMatrix2();    // Матрица "стоимости (расстояний)"
    vector<double> push(N); //поток из конечно в начальную вершину
    vector<int>pred(N);        // Откуда пришли в вершину [v] (предок)
    vector<int>path;
    path.emplace_back(s);
    bool k = false;
    while (bfs(s, t, St, MAX_Flow,F,C,push,pred))
    {
        int add = push[t];
        v = t; u = pred[v];
        while (v != s)
        {
            F[u][v] += add;
            F[v][u] -= add;
            v = u; u = pred[v];
            if(v!=0&&v!=s)
            path.emplace_back(v);
            k = true;
        }
        
        flow += add;
    }
    path.emplace_back(t);//выводим путь максмального веса
    if (!k) {
        cout << "Нет пути" << endl;
        return NULL;
    }
    for (auto it = begin(path);it != end(path);++it) {
       if (position_station_invert.find(*it) != position_station_invert.end()) {
           if (it == begin(path)) cout << position_station_invert.find(*it)->second; else
               cout << "->" << position_station_invert.find(*it)->second;
       }
   }
    return max_flow = flow;
}

void NetWork::ViewNetwork(const NetWork& CurrentNetwork)
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
            cout << setw(7) << matrix[i][j];
        cout << endl;
    }
}
