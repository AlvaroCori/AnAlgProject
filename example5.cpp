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
/*
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
            cout<<Graph.size()<<endl;
            int r = 0;
            for(auto v: Graph){
                if(Ids[v.first] == -1){
                    r = r+1;
                    id = -1;
                    cout<<"w"<<endl;
                    dfs_tharjan(it->first);
                }
            }
            cout<<"se metio dfs en: "<<r<<endl;
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
                while(Stack.top()!=at){
                    string node = Stack.top();
                    Stack.pop();
                    on_stack[node] = true;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }

};*/

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
                    dfs_tharjan(it->first);
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
                    on_stack[node] = true;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }
        
       /*
        void dfs_tharjan(string at)
        {
            string o_at = at;
            stack<string> dfs;
            vector<string> updated;
            int min_l = 0;
            dfs.push(at);
            while(dfs.empty() == false){
                at = dfs.top();
                dfs.pop();
                Stack.push(at);
                on_stack[at] = true;
                id = id + 1;
                Ids[at] = id;
                Low[at] = id;
                //Visit all neighbours & min low-linkon callback
                for(auto to : Graph[at]){
                    if (Ids[to] == -1){
                        dfs.push(to);
                        updated.push_back(to);
                        //dfs_tharjan(to);
                        //Low[at] = min(Low[at], Low[to]);
                        continue;
                    } 
                    if (on_stack[to]){
                        Low[at] = min(Low[at], Low[to]);
                    }
                }
                //id = id - 1;
            }
            for (auto up : updated)
            {
                min_l = min(min_l, Low[up]);
            }
            for (auto up : updated)
            {
                Low[up] = min_l;
            }
            at = o_at;
            //After exploring all neighbors
            if (Ids[at] == Low[at])
            {
                while(Stack.top()!=at){
                    string node = Stack.top();
                    Stack.pop();
                    on_stack[node] = true;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }//at 1
        */
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
                int er;
                cout<<"duplicadooooooooooooooo";
                cin>>er;
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
            int fl = 196;
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
    cout<<"Se capto "<<reader.Graph.Graph.size()<<" usuarios."<<endl;
    cout<<"La cantidad de componentes conexas es de "<<endl;
    reader.Graph.realize_tharjan();
    cout<<reader.Graph.scc_count<<endl;
    ///cout<<reader.get_comp_conexes()<<endl;
    return 0;
}


/*
'''

#https://github.com/morris821028/UVa/blob/master/volume113/11324%20-%20The%20Largest%20Clique.cpp

def tarjan(N, S, T, edges):
    cnt = 0
    bridges = []
    visit = [0 for i in range(N)]
    low = [N + 1 for i in range(N)]
    ret = [False for i in range(N)]
    q = [0 for i in range(N + 1)]
    q[0] = (S, -1, -1)
    top = 0
    while top >= 0:
        i, father, v = q[top]
        if v == -1:
            ret[i] = (i == T)
            cnt = cnt + 1
            visit[i] = low[i] = cnt
        elif v < len(edges[i]):
            j, w, flag = edges[i][v]
            if flag:
                if j == q[top + 1][0]:
                    ret[i] = ret[i] or ret[j]
                    if ret[i]: low[i] = min(low[i], low[j])
        v += 1
        q[top] = (i, father, v)
        if v < len(edges[i]):
            j, w, flag = edges[i][v]
            if flag:
                if not visit[j]:
                    top += 1
                    q[top] = (j, i, -1)
            else:
                if j != father and visit[j]:
                    low[i] = min(low[i], visit[j])
        else:
            if low[i] == visit[i] and ret[i]:
                if father >=0:
                    bridges.append((father, i))
            top -= 1

    #print "visit", visit
    #print "low", low
    #print "ret", ret
    return bridges
    
g = []
g.append([])
g.append([1, 2])
g.append([2, 1])
g.append([3, 4])
g.append([4, 3])

vertices = [1,2,3,4]
#print(scc2(g, vertices))

'''
*/

/*
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
                    dfs_tharjan(it->first);
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
                    on_stack[node] = true;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }
        
        void dfsd_tharjan(string at)
        {
            string o_at = at;
            stack<string> dfs;
            vector<string> updated;
            int min_l = 0;
            dfs.push(at);
            while(dfs.empty() == false){
                at = dfs.top();
                dfs.pop();
                Stack.push(at);
                on_stack[at] = true;
                id = id + 1;
                Ids[at] = id;
                Low[at] = id;
                //Visit all neighbours & min low-linkon callback
                for(auto to : Graph[at]){
                    if (Ids[to] == -1){
                        dfs.push(to);
                        updated.push_back(to);
                        //dfs_tharjan(to);
                        //Low[at] = min(Low[at], Low[to]);
                        continue;
                    } 
                    if (on_stack[to]){
                        Low[at] = min(Low[at], Low[to]);
                    }
                }
                //id = id - 1;
            }
            for (auto up : updated)
            {
                min_l = min(min_l, Low[up]);
            }
            for (auto up : updated)
            {
                Low[up] = min_l;
            }
            at = o_at;
            //After exploring all neighbors
            if (Ids[at] == Low[at])
            {
                while(Stack.top()!=at){
                    string node = Stack.top();
                    Stack.pop();
                    on_stack[node] = true;
                    Low[node] = Ids[at];
                }
                scc_count++;
            }
        }//at 1
        
};

int main()
{
    
    #4 2
    #1 2 2
    #3 4 2
    
    Graph graph;
    graph.Graph.insert(pair<string, set<string>>("1",set<string>({"2","3"})));
    graph.Graph.insert(pair<string, set<string>>("2",set<string>({"1"})));
    graph.Graph.insert(pair<string, set<string>>("3",set<string>({})));

    //graph.Graph.insert(pair<string, set<string>>("8",set<string>({})));
    //graph.Graph.insert(pair<string, set<string>>("9",set<string>({"1"})));
    graph.realize_tharjan();
    cout<<graph.scc_count<<endl;
    return 0;
}
*/