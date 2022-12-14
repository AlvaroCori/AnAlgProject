#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstring>
using namespace std;


map<string, set<string>> Graph;
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
            if (Graph[node].find(remaining) != Graph[node].end())
            {
                new_remaining_nodes.insert(remaining);
            }
        }
        new_skip_nodes = vector<string>();
        for (auto skip : skip_nodes)
        {
            if (Graph[node].find(skip) != Graph[node].end())
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
int main(){
    set<string> a1;
    a1.insert("2");
    a1.insert("3");
    a1.insert("4");
    a1.insert("5");
    Graph.insert(pair<string,set<string>>("1",a1));
    set<string> a2;
    a2.insert("1");
    a2.insert("3");
    a2.insert("4");
    a2.insert("5");
    Graph.insert(pair<string,set<string>>("2",a2));
    set<string> a3;
    a3.insert("1");
    a3.insert("2");
    a3.insert("4");
    a3.insert("5");
    Graph.insert(pair<string,set<string>>("3",a3));
    set<string> a4;
    a4.insert("1");
    a4.insert("2");
    a4.insert("3");
    a4.insert("5");
    Graph.insert(pair<string,set<string>>("4",a4));
    set<string> a5;
    a5.insert("1");
    a5.insert("2");
    a5.insert("3");
    a5.insert("4");
    Graph.insert(pair<string,set<string>>("5",a5));
    set<string> r;
    r.insert("1");
    r.insert("2");
    r.insert("3");
    r.insert("4");
    r.insert("5");
    vector<string> a, b;
    //cout<<Graph["1"].size()<<endl;
    cout<<find_cliques(a, r, b)<<endl;
    return 0;
    
}

/*
def find_cliques(potential_clique=[], remaining_nodes=[], skip_nodes=[], depth=0):

    if len(remaining_nodes) == 0 and len(skip_nodes) == 0:
        print('This is a clique:', potential_clique)
        return 1

    found_cliques = 0
    for node in remaining_nodes:

        # Try adding the node to the current potential_clique to see if we can make it work.
        new_potential_clique = potential_clique + [node]
        new_remaining_nodes = [n for n in remaining_nodes if n in node.neighbors]
        new_skip_list = [n for n in skip_nodes if n in node.neighbors]
        found_cliques += find_cliques(new_potential_clique, new_remaining_nodes, new_skip_list, depth + 1)

        # We're done considering this node.  If there was a way to form a clique with it, we
        # already discovered its maximal clique in the recursive call above.  So, go ahead
        # and remove it from the list of remaining nodes and add it to the skip list.
        remaining_nodes.remove(node)
        skip_nodes.append(node)
    return found_cliques
*/
///https://iq.opengenus.org/bron-kerbosch-algorithm/
///https://dl.acm.org/doi/10.1145/362342.362367