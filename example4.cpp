#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <queue>
#include <limits.h>
using namespace std;
class Graph{
    public:
        vector<bool> Graph_r[77001];//Este grafo toma menos memoria
        map<string, set<string>> Graph;
        int size;
        vector<int> Dijkstra(int exit_node){
            priority_queue < pair<int, int>> priority;
            vector<int> distance;
            vector<bool> visited;
            int index, y, length, new_distance;
            for( int i = 0; i <= size; i++ ){ 
                distance.push_back(INT_MAX);
                visited.push_back(false);
            };
            priority.push( pair<int, int>(exit_node, 0));
            distance[exit_node] =0;
            visited[exit_node] = true;
            while( priority.size() > 0){
                index = priority.top().first;
                length = priority.top().second;
                priority.pop();
                for(int neighbor = 1; neighbor<=size;neighbor= neighbor + 1){
                    if (Graph_r[index][neighbor] == false)
                    {
                        continue;
                    }
                    y = neighbor;
                    if (visited[y])
                    {
                        continue;
                    }
                    new_distance = distance[index] + 1;
                    if( new_distance < distance[y]){
                        distance[y] = new_distance;
                        priority.push(pair<int, int>(y, 1));
                    }
                }
            }
            return distance;
        }
        
};
class ReaderFiles
{
    vector<string> Paths;
    map<string, int> Dictionary;
    public:
        Graph Graph;
        void get_files(string txt_file)
        {
            string path;
            ifstream ReadFile(txt_file);
            while (getline(ReadFile, path)) {
                Paths.push_back(path);
            }
            ReadFile.close();
        }
        string get_substring(string file_name, char element, int init)
        {
            string sub_string = "";
            for (int i = init; i<file_name.length(); i++)
            {
                if (file_name[i] == element)
                {
                    break;
                }
                sub_string = sub_string + file_name[i];
            }
            return sub_string;
        }
        vector<string> split(string line,char separator)
        {
            vector<string> elements;
            string element = "";
            for (int i = 0; i<line.length();i++)
            {
                if (line[i] == separator)
                {
                    elements.push_back(element);
                    element = "";
                }
                else{
                    element = element + line[i];
                }
            }
            return elements;

        }
        vector<string> split(string line)
        {
            vector<string> elements;
            string element = "";
            for (int i = 0; i<line.length();i++)
            {
                if (isalpha(int(line[i])) == false && isdigit(int(line[i]))==false)
                {
                    elements.push_back(element);
                    element = "";
                }
                else{
                    element = element + line[i];
                }
            }
            return elements;

        }
        set<string> join_sets(set<string> set_1, set<string> set_2)
        {
            for (auto element: set_2)
            {
                set_1.insert(element);
            }
            return set_1;
        }
        bool add_vertice(string id)
        {
            bool not_exist_vertice = Graph.Graph.count(id) <= 0;
            if (not_exist_vertice)
            {
                Graph.Graph.insert(pair<string, set<string>>(id, set<string>()));
            }
            return not_exist_vertice;

        }
        bool add_edge(string origin, string neighbor)
        {
           if (Graph.Graph.find(origin) == Graph.Graph.end())
            {
                add_vertice(origin);
            }
            if (Graph.Graph.find(neighbor) == Graph.Graph.end())
            {
                add_vertice(neighbor);
            }
            bool exist_edge = Graph.Graph[origin].find(neighbor) != Graph.Graph[origin].end();
            if (exist_edge == false){
                Graph.Graph[origin].insert(neighbor);
            }
            return ~exist_edge; 
        }
        void load_graph()
        {
            enum type_files { edges = 0, circles = 1, feat = 2, egofeat = 3, featnames = 4};
            int complete_path_size = 66;
            int lines, files = 0;
            string line, name_file, name, type_file;
            int max = 0;
            int limit = 451;
            for (auto path: Paths)
            {
                limit = limit - 1;
                cout<<limit<<endl;
                if (limit == 0)
                {
                    break;
                }
                ifstream ReadFile(path);
                lines = 0;
                name_file = path.substr(complete_path_size-1, path.length());
                name = get_substring(name_file, '.', 0);
                type_file = path.substr(complete_path_size+name.length(), path.length()-1);
                add_vertice(name);
                while (getline(ReadFile, line)) {
                    lines = lines + 1;
                    if (type_file == "edges")
                    {
                        string idx, idy;
                        idx = get_substring(line, ' ', 0);
                        idy = get_substring(line, ' ', idx.length()+1);
                        add_vertice(idx);
                        add_vertice(idy);
                        add_edge(name, idx);
                        add_edge(idx, name);
                        add_edge(idx, idy);
                        add_edge(idy, idx);
                        continue;
                    }
                }
                files = files + 1;
                cout<<name<<" "<<type_file<<endl;

                ReadFile.close();
            }
            cout<<"Se leyo "<<files<<" archivos."<<endl;
        }
        void convert_graph()
        {
            int i = 1;
            Graph.size = Graph.Graph.size();
            for (auto v: Graph.Graph)
            {
                Dictionary[v.first]= i;
                Graph.Graph_r[i] = vector<bool>(Graph.size, false);
                i = i + 1;
            }
            for (auto v: Graph.Graph)
            {
                i = Dictionary[v.first];
                for (auto n: v.second)
                {
                    Graph.Graph_r[i][Dictionary[n]] = true;
                }
            }

        }
        float get_distances()
        {
            vector<int> distances = Graph.Dijkstra(1);
            int sum = 0;
            float average = 0;
            for (int d = 1; d<distances.size(); d++)
            {
                sum = sum + d;
            }
            average = sum / distances.size();
            cout<<sum<<" / "<<distances.size()<<" = "<<endl;
            return average;
        }
};


int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.load_graph();
    reader.convert_graph();
    cout<<"La distancia promedio es: "<<endl;
    int n = reader.get_distances();
    cout<<n<<endl;
    return 0;
}
///g++ -O2 -std=c++11 -Wall -Wl,--stack=268435456 example5.cpp -o example.exe
//268 MB