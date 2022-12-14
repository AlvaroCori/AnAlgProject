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
        map<string, bool> Visited;
        map<string, int> Paths;
        int max_path = 0;
        /*
        void dfs(string vertice, int level = 0)
        {
            Visited[vertice] = true;
            for (auto neighbor : Graph[vertice])
            {
                if (Visited[neighbor] == false){
                    dfs(neighbor, level+1);
                }
                else{
                    //cout<<"vav "<<level<<endl;
                    max_path = max(max_path, level);
                    //cout<<"d "<<max_path<<endl;
                    //Paths[vertice] = max(Paths[vertice], Paths[neighbor]+1);
                }
            }
        }
        El camino mas largo es: 15422
        */
       int ll=0;
        void dfs(string vertice, int level = 0)
        {
            stack<pair<string, int>> dfs_stack;
            dfs_stack.push(pair<string, int>(vertice,level));
            
            while(dfs_stack.empty() == false){
                auto stack_e = dfs_stack.top();
                vertice = stack_e.first;
                level = stack_e.second;
                dfs_stack.pop();
                if (Visited[vertice]==false){
                    ll = ll + 1;
                    if (ll%1000 == 0)
                        cout<<ll<<endl;
                    //if (ll>17000)
                    //{
                    //    cout<<ll<<endl;
                    //}
                }
                Visited[vertice] = true;

                for (auto neighbor : Graph[vertice])
                {
                    if (Visited[neighbor] == false){
                        //level = level + 1;
                        //dfs(neighbor, level);
                        //level = level -1;
                        dfs_stack.push(pair<string, int>(neighbor,level+1));
                    }
                    else{
                        //cout<<"vav "<<level<<endl;
                        max_path = max(max_path, level);
                        //cout<<"d "<<max_path<<endl;
                        //Paths[vertice] = max(Paths[vertice], Paths[neighbor]+1);
                    }
                }
            }
        }
        
        int long_path()
        {
            set<string> vertices;
            //int max_path = 0;
            for (auto vertice: Graph)//Grafo no esta 
            {
                vertices.insert(vertice.first);
                Visited[vertice.first] = false;
                Paths[vertice.first] = 0;
            } 
            for (auto vertice: vertices)
            {
                if (Visited[vertice] == false){
                    dfs(vertice);
                }
            }
            /*
            for (auto path: Paths)
            {
                max_path = max(max_path, path.second);
            }*/
            return max_path;
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
            int fl = 601;
            for (auto path: Paths)
            {
                fl = fl - 1;
                cout<<fl<<endl;
                if (fl == 0)
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
                        add_vertice(idx);
                        add_edge(name, idx);
                        add_edge(idx, name);
                        add_edge(idx, idy);
                        add_edge(idy, idx);
                        continue;
                    }
                    /*
                    if (type_file == "circles")
                    {
                        vector<string> values = split(line);
                        for (int i = 1; i < values.size() ; i++)
                        {
                            vertices_circles.insert(values[i]);
                        }
                        continue;
                    }
                    if (type_file == "feat")
                    {
                        vector<string> values = split(line, ' ');
                        vertices_feat.insert(values[0]);
                        continue;
                    }
                    */
                }
                files = files + 1;
                /*
                cout<<path<<endl;
                cout<<"lineas: "<<lines<<endl;
                */
                cout<<name<<" "<<type_file<<endl;

                ReadFile.close();
            }
            cout<<"Se leyo "<<files<<" archivos."<<endl;
        }
        int long_path()
        {
            return Graph.long_path();
        }
};


int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.load_graph();
    cout<<"Se capto "<<reader.Graph.Graph.size()<<" usuarios."<<endl;
    cout<<"El camino mas largo es: "<<reader.Graph.long_path()<<endl;

    ///cout<<reader.get_comp_conexes()<<endl;
    return 0;
}
///El camino mas largo es: 15420


/*
14000
15000
16000
17000
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
*/