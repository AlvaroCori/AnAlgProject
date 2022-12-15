#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cstring>

using namespace std;

class Graph{
    public:
        map<string, set<string>> Graph;
        vector<bool> Visited;
        map<string,int> Ids;
        map<string,int> Low;
        stack<string> Stack;
        map<string, bool> on_stack;
        int id;
        int scc_count = 0;
        void realize_tharjan(){
            id = 0;
            scc_count = 0;
            for (auto v : Graph)
            {
                on_stack.insert(pair<string, bool>(v.first, false));
                Ids.insert(pair<string, int>(v.first, -1));
                Low.insert(pair<string, int>(v.first, -1));
            }
            auto it = Graph.begin();
            for(auto v: Graph){
                if(Ids[v.first] == -1){
                    id = -1;
                    dfs_tharjan(v.first);
                }
            }
        }
        
        void dfs_tharjan(string at)
        {
            Stack.push(at);
            on_stack[at] = true;
            id = id + 1;
            Ids[at] = id;
            Low[at] = id;
            //Visit all neighbours & min low-linkon callback
            for(auto to : Graph[at]){
                if (Ids[to] == -1){
                    dfs_tharjan(to);
                    Low[at] = min(Low[at], Low[to]);
                    continue;
                } 
                if (on_stack[to]){
                    Low[at] = min(Low[at], Low[to]);
                }
            }
            //After exploring all neighbors
            if (Ids[at] == Low[at])
            {
                //cout<<"at "<<at<<endl;
                while(Stack.top()!=at){
                    string node = Stack.top();
                    Stack.pop();
                    on_stack[node] = false;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }
};

class ReaderFiles
{
    vector<string> Paths;
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
            for (auto path: Paths)
            {
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
                        add_vertice(idx);
                        add_edge(name, idx);
                        add_edge(idx, idy);
                        continue;
                    }               
                }
                files = files + 1;
                cout<<name<<" "<<type_file<<endl;
                ReadFile.close();
            }
            cout<<"Se leyo "<<files<<" archivos."<<endl;
        }
        int get_comp_conexes()
        {
            Graph.realize_tharjan();
            return Graph.scc_count;
        }     
};


int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.load_graph();
    reader.Graph.realize_tharjan();
    cout<<"La cantidad de componentes conexas es de "<<reader.Graph.scc_count<<"."<<endl;
    return 0;
}

///g++ -O2 -std=c++11 -Wall -Wl,--stack=268435456 example5.cpp -o example.exe
//268 MB

/*
Se leyo 792 archivos.
La cantidad de componentes conexas es de 2431.
*/