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
        void count_users()
        {
            enum type_files { edges = 0, circles = 1, feat = 2, egofeat = 3, featnames = 4};
            int complete_path_size = 66;
            int lines, files = 0;
            string line, name_file, name, type_file;
            set<string> vertices_files;
            set<string> vertices_edges;
            set<string> vertices_circles;
            set<string> vertices_feat;
            set<string> vertices;
            int max = 0;
            for (auto path: Paths)
            {
                ifstream ReadFile(path);
                lines = 0;
                name_file = path.substr(complete_path_size-1, path.length());
                name = get_substring(name_file, '.', 0);
                type_file = path.substr(complete_path_size+name.length(), path.length()-1);
                vertices_files.insert(name);
                while (getline(ReadFile, line)) {
                    lines = lines + 1;
                    if (type_file == "edges")
                    {
                        string idx, idy;
                        idx = get_substring(line, ' ', 0);
                        idy = get_substring(line, ' ', idx.length()+1);
                        vertices_edges.insert(idx);
                        vertices_edges.insert(idy);
                        continue;
                    }
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
                }
                files = files + 1;
                cout<<name<<" "<<type_file<<endl;

                ReadFile.close();
            }
            vertices = join_sets(vertices, vertices_files);
            vertices = join_sets(vertices, vertices_edges);
            vertices = join_sets(vertices, vertices_circles);
            vertices = join_sets(vertices, vertices_feat);
            cout<<"Se leyo "<<files<<" archivos."<<endl;
            cout<<"Existen "<<vertices_files.size()<<" usuarios en los nombres de archivos."<<endl;
            cout<<"Existen "<<vertices_edges.size()<<" usuarios en los archivos edge."<<endl;
            cout<<"Existen "<<vertices_circles.size()<<" usuarios en los archivos circles."<<endl;
            cout<<"Existen "<<vertices_feat.size()<<" usuarios en los archivos feat."<<endl;
            cout<<"Existen "<<vertices.size()<<" en total de usuarios."<<endl;
        }
};


int main(){
    ReaderFiles reader;
    reader.get_files("list.txt");
    reader.count_users();
    return 0;
}


//g++ -O2 -std=c++11 -Wall -Wl,--stack=268435456 example1.cpp -o example.exe