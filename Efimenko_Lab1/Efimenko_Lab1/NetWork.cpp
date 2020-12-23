#include "NetWork.h"
#include <queue>

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
vector<vector<double>> NetWork::GetMatrix() const
{
    return matrix;
}

vector<vector<double>> NetWork::GetMatrix2() const
{
    return matrix2;
}

set<int> NetWork::GetPipes() const
{
    return involved_Pipes;
}

set<int> NetWork::GetStations() const
{
    return involved_Stations;
}
void NetWork::SetmatrixL(vector<vector<double>> new_matrix)
{
    matrix = new_matrix;
}
void NetWork::SetmatrixW(vector<vector<double>> new_matrix)

{
    matrix2 = new_matrix;
}
unordered_map<int, int> NetWork::GetPosition() const
{
    return position_station;
}
void NetWork::PrintS(const unordered_map <int, int>& m) {
    for (auto& i : m) {
        cout << i.first << i.second << endl;
    }
}

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
                    matrix[indexi][indexj] = item.second.GetLength();
                    matrix2[indexi][indexj] = item.second.GetLength();
                }
                break;
            }
        }
    }
   /* if (sort.size() == 0) {
        cout << "Нет связей для графа" << endl;
        return;
    }*/
    Current_Network.SetmatrixL(matrix);
    Current_Network.SetmatrixW(matrix2);
    ViewNetwork(matrix, involved_Stations);
    unordered_set<int>sort = Topological_Sort(Current_Network);
    
    cout << "Топологическая сортировка" << endl;
    for (auto it = begin(sort);it != end(sort);++it) {
        if (position_station_invert.find(*it) != position_station_invert.end()) {
            if  (it== begin(sort)) cout << position_station_invert.find(*it)->second; else
                cout << "->" << position_station_invert.find(*it)->second;
        }
    }
}
unordered_set<int> NetWork::Topological_Sort(NetWork& Current_Network) {
    vector<vector<double>> matrix_for_sort;
    int N = Current_Network.GetStations().size();
    double sum = 0;
    unordered_set<int>sort;
    vector <int> visit(N, 0);
    for (int i = 0; i < N; i++)
        matrix_for_sort.push_back(vector<double>());
    matrix_for_sort = Current_Network.GetMatrix();
    for (int i = 0; i < N; i++) {
        if (cycle(i, matrix_for_sort, visit)) {
            cout << "В графе есть цикл" << endl;
            return sort;
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
    return sort;
}



//////////////////////////////////////////////////////////////////////////////// max flow

void NetWork::BFS(const NetWork& Current_Network,int start, int end) {
    vector<vector<double>> matrix_for_length = Current_Network.matrix;
    int s=start;              		// Номер исходной вершины
    int g=end;              		// Номер конечной вершины
    int N = Current_Network.involved_Stations.size();

    int infinity = 10000;
    int v;
    vector <int> x (N); //Массив, содержащий единицы и нули для каждой вершины,
                   // x[i]=0 - еще не найден кратчайший путь в i-ю вершину,
                   // x[i]=1 - кратчайший путь в i-ю вершину уже найден
    vector <int>t(N);  //t[i] - длина кратчайшего пути от вершины s в i
    vector <double>h(N);  //h[i] - вершина, предшествующая i-й вершине
                  // на кратчайшем пути

    // Инициализируем начальные значения массивов
    int u;		    // Счетчик вершин
    for (u = 0;u < N;u++)
    {
        t[u] = infinity; //Все пути бесконечности 
        x[u] = 0;        // и нет кратчайшего пути ни для одной вершины
    }
    h[s] = 0; // s - начало пути, поэтому этой вершине ничего не предшествует
    t[s] = 0; // Кратчайший путь из s в s равен 0
    x[s] = 1; // Для вершины s найден кратчайший путь
    v = s;    // Делаем s текущей вершиной

    while (1)
    {
        // Перебираем все вершины, смежные v, и ищем для них кратчайший путь
        for (u = 0;u < N;u++)
        {
            if (matrix_for_length[v][u] == 0)continue; // Вершины u и v несмежные
            if (x[u] == 0 && t[u] > t[v] + matrix_for_length[v][u]) //Если кр.путь еще не найден
            {
                t[u] = t[v] + matrix_for_length[v][u];	//новый путь короче
                h[u] = v;
            }
        }
        // Ищем из всех длин некратчайших путей самый короткий
        int w = infinity; 
        v = -1;           
        for (u = 0;u < N;u++) // Перебираем все вершины.
        {
            if (x[u] == 0 && t[u] < w) // Если для вершины не найден кратчайший 
                                  // путь и если длина пути в вершину u меньше
                                  // уже найденной, то
            {
                v = u; // текущей вершиной становится u-я вершина
                w = t[u];
            }
        }
        if (v == -1)
        {
            cout << "Нет пути из вершины " << s << " в вершину " << g  << endl;
            break;
        }
        if (v == g) // Найден кратчайший путь,
        {        // выводим его
            cout << "Кратчайший путь из вершины " << s << " в вершину " << g << ":";
            u = g;
            while (u != s)
            {
                cout << " " << u;
                u = h[u];
            }
            cout << " " << s << ". Длина пути - " << t[g];
            break;
        }
        x[v] = 1;
    }
}
    //queue<int> Q;
    ////distance[i] - расстояние от i-ой вершины до стартовой
    //vector<int> distance(matrix_for_length.size(), -1);
    ////prevTop[i] - предок i-ой вершины в кратчайшем пути
    //vector<int> prevTop(matrix_for_length.size(), -1);

    //distance[start] = 0;
    //Q.push(start);
    //while (Q.size()) {
    //    int u = Q.front();
    //    Q.pop();
    //    for (int j = 0; j < matrix_for_length[u].size(); j++) {
    //        int v = matrix_for_length[u][j];
    //        if (distance[v] == -1) {
    //            distance[v] = distance[u] + 1;
    //            prevTop[v] = u;
    //            Q.push(v);
    //        }
    //    }
    //}

    ////print results
    //for (int i = 0; i < prevTop.size(); i++) {
    //    cout << i << '(' << distance[i] << ")\t:";
    //    int x = prevTop[i];
    //    while (x != -1) {
    //        cout << x << ' ';
    //        x = prevTop[x];
    //    }
    //    cout << endl;
    //}

    //return;

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
    auto C = current_Network.GetMatrix();    // Матрица "пропускных способностей"
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
