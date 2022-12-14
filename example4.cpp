#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

//Use this
using namespace std;

class Graph{
    public:
        vector<bool> Graph[70001];//Este grafo toma menos memoria
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
                    if (Graph[index][neighbor] == false)
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

int main(){
    int n = 70000;
    Graph graph;
    graph.size = n;
    graph.Graph[0] = vector<bool>();
    for (int i =1;i<=n;i++){
        graph.Graph[i] = vector<bool>(n, false);
        for (int j = 1;j<=n;j++)
        {
            if (i != j){
                graph.Graph[i][j] = true;
            }
            
        }
    }
    vector<int> distance = graph.Dijkstra(1);
    int sum = 0;
    for (int i = 1;i<distance.size();i++)
    {
        sum = sum + distance[i];
    }
    cout<<sum<<" / "<<distance.size()-1<<endl;
	return 0;
}


///"stack": "108435456"