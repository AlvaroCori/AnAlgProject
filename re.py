from itertools import combinations
import networkx as nx


def k_cliques(graph):
    cliques = [{i, j} for i, j in graph.edges() if i != j]
    k = 2
    while cliques:
        yield k, cliques
        cliques_1 = set()
        for u, v in combinations(cliques, 2):
            w = u ^ v
            if len(w) == 2 and graph.has_edge(*w):
                cliques_1.add(tuple(u | w))
        cliques = list(map(set, cliques_1))
        k += 1


def max_cliques(graph, size_k):
    max_k = 0
    for k, cliques in k_cliques(graph):#consigue todos los cliques
        if (max_k < k):
            max_k = k 
    return max_k


size_k = 3
graph = nx.Graph()
graph.add_nodes_from(["1", "2", "3", "4"])
graph.add_edge("1", "1")
graph.add_edge("1", "2")
graph.add_edge("1", "3")
graph.add_edge("2", "1")
graph.add_edge("2", "2")
graph.add_edge("2", "3")
graph.add_edge("3", "1")
graph.add_edge("3", "2")
graph.add_edge("3", "3")
graph.add_edge("4","1")
graph.add_edge("1","4")

print(f"El clique mas grande es {max_cliques(graph, size_k)}")

#https://iq.opengenus.org/algorithm-to-find-cliques-of-a-given-size-k/

