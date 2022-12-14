#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstring>
using namespace std;
class Graph
{
    public:
        map<string, set<string>> Graph;
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
        bool add_edge(string origin, string neigbhor)
        {
            bool exist_edge = Graph.Graph[origin].find(neigbhor) != Graph.Graph[origin].end();
            if (exist_edge == false){
                Graph.Graph[origin].insert(neigbhor);
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
        int find_cliques(vector<string> potential_clique, set<string> remaining_nodes, vector<string> skip_nodes, int max_cliques = 0)
        {
            set<string> new_remaining_nodes, aux;
            vector<string> new_skip_nodes, new_potential_clique;
            if (remaining_nodes.size() == 0 && skip_nodes.size() == 0 && max_cliques < potential_clique.size())
            {
                max_cliques = potential_clique.size();
            }
            aux = remaining_nodes;
            for (auto node : aux)
            {
                new_potential_clique = potential_clique;
                new_potential_clique.push_back(node);
                new_remaining_nodes = set<string>();
                for (auto remaining : remaining_nodes)
                {
                    if (Graph.Graph[node].find(remaining) != Graph.Graph[node].end())
                    {
                        new_remaining_nodes.insert(remaining);
                    }
                }
                new_skip_nodes = vector<string>();
                for (auto skip : skip_nodes)
                {
                    if (Graph.Graph[node].find(skip) != Graph.Graph[node].end())
                    {
                        new_skip_nodes.push_back(skip);
                    }
                }
                max_cliques = find_cliques(new_potential_clique, new_remaining_nodes, new_skip_nodes, max_cliques);
                remaining_nodes.erase(node);
                skip_nodes.push_back(node);
            }
            return max_cliques;
        }
        int get_max_cliques()
        {
            vector<string> potential_clique, skip_nodes;
            set<string> remainings;
            for (auto vertice : Graph.Graph)
            {
                remainings.insert(vertice.first);
            }
            return find_cliques(potential_clique, remainings, skip_nodes);
        }     
};


int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.load_graph();
    cout<<"Se capto "<<reader.Graph.Graph.size()<<" usuarios."<<endl;
    cout<<"El mayor clique es de "<<reader.get_max_cliques()<<endl;
    return 0;
}
