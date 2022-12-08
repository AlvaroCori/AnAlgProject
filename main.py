class Node(object):
    def __init__(self, id):
        ''' assumes name a string '''
        self.id = id
        
    def get_id(self):
        return self.id
    
    def __str__(self):
        return self.id

class Edge(object):
    def __init__(self, src, dest):
        '''assume src and dest are strings '''
        self.src = src
        self.dest = dest

    def get_source(self):
        return self.src

    def get_destination(self):
        return self.dest

    def __str__(self):
        return self.src + '-->' + \
            self.dest

class Digraph(object):
    def __init__(self):
        self.nodes = []
        self.edges = {}

    def add_node(self, nodeId):
        if not self.has_node(nodeId):
            node = Node(nodeId)
            self.nodes.append(node)
            self.edges[node] = []
            
    def printNodes(self):
        for node in self.nodes:
            print(node.get_id())
    def get_number_of_nodes(self):
        return len(self.nodes)

    def add_edge(self, edge):
        srcId = edge.get_source()
        destId = edge.get_destination()
        src = None
        dest = None
        for node in self.nodes:
            if(node.get_id() == srcId):
                src = node
            if(node.get_id() == destId):
                dest = node
            

        self.edges[src].append(dest)

    def children_of(self, node):
        return self.edges[node]

    def has_node(self, nodeId):
        isCreated = False
        for i in self.nodes:
            if(len(self.nodes) == 0):
                break
            if i.get_id() == nodeId:
                isCreated = True
                break
        return isCreated

    def __str__(self):
        result = ''
        for src in self.nodes:
            for dest in self.edges[src]:
                result = result + src.get_id() + \
                    '-->' + dest.get_id() + '\n'
        return result[:-1]

if __name__ == '__main__' :    
    # create the graph
    graph = Digraph()
    comprobante = []
    reducido = []
    cont = 0
    with open('list.txt') as f:
        lines = f.readlines()
    for line in lines:
        if '.edges' in line:
            originId = line.split('\\').pop().split('.').pop(0)
            
            comprobante.append(originId)
            graph.add_node(originId)
            with open(line[:-1]) as f2:
                allData = f2.readlines()
            for data in allData:
                relationLine = data.split()
                idX = relationLine[0]
                idY = relationLine[1]
                
                comprobante.append(idX)
                comprobante.append(idY)
                
                graph.add_node(idX)
                graph.add_node(idY)
                
                edgeOX = Edge(originId, idX)
                edgeXY = Edge(idX, idY)

                graph.add_edge(edgeOX)
                graph.add_edge(edgeXY)

                cont = cont + 1
                reducido = set(comprobante)
                if(cont == 166901):
                    break
            print('Leido el archivo numero', cont)
        if(cont == 166901):
            break

    

    # create the nodes
    ##node_a = Node('A')
    
    # add the nodes to the graph
    ##graph.add_node(node_a)
   
    # then create the edges
    ##edge_ab = Edge(node_a, node_b)
   
    # add the edges to the graph
    ##graph.add_edge(edge_ab)
   
    # print the graph
    print('The nodes and edges in the graph are:')
    print(graph.get_number_of_nodes())
    print('The nodes and edges in the list are:')
    print(len(reducido))
    #graph.printNodes()
    ##print(graph)
    #print()
    # print children of node C
    #print('Nodes connected to C are:')
    #for i in graph.children_of(node_c):
        #print(i)


