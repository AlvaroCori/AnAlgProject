#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
class Graph
{
    vector<long long> Graph;
};
class ReaderFiles
{
    vector<string> Paths;
    Graph Graph;
    public:
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
        void read_files()
        {
            enum type_files { edges = 0, circles = 1, feat = 2, egofeat = 3, featnames = 4};
            int complete_path_size = 94;
            int lines, files = 0, users = 0;
            string line, name_file, name, type_file;
            set<string> vertices;
            for (auto path: Paths)
            {
                ifstream ReadFile(path);
                lines = 0;
                name_file = path.substr(complete_path_size-1, path.length());
                name = get_substring(name_file, '.', 0);
                type_file = path.substr(complete_path_size+name.length(), path.length()-1);
                vertices.insert(name);

                while (getline(ReadFile, line)) {
                    lines = lines + 1;
                    if (type_file == "edges")
                    {
                        string idx, idy;
                        idx = get_substring(line, ' ', 0);
                        idy = get_substring(line, ' ', idx.length()+1);
                        vertices.insert(idx);
                        vertices.insert(idy);
                        continue;
                    }
                }
                if (type_file == "edges")
                {
                    users = users + 1;
                }
                
                files = files + 1;
                cout<<path<<endl;
                cout<<"lineas: "<<lines<<endl;
                cout<<name<<" "<<type_file<<endl;
                ReadFile.close();
            }
            cout<<"Se leyo "<<files<<" archivos."<<endl;
            cout<<"Existen "<<users<<" usuarios encontrados."<<endl;
            cout<<"Existen "<<vertices.size()<<" nodos."<<endl;
            std::cin.ignore();
        }
};

//C:\Users\Augusto Valdez\Documents\My Data\Projects\UCB\Analisis de Algoritmos\Proyecto\gplus
int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.read_files();
    return 0;
}


///132 nodos segun el nombre de los archivos.

//Existen 102119 nodos leyendo los nodos de los archivos edges