class Vertex:
  
    def __init__(self, key):
        self.id = key
        self.connectedTo = {}
        
    def addNeighbor(self, nbr, weight = 0):
        self.connectedTo[nbr] = weight
        
    def __str__(self):
        return f"{str(self.id)} connected to: {str([x.id for x in self.connectedTo])}"
      
    def getConnections(self):
        return self.connectedTo.keys()
        
    def getId(self):
        return self.id
      
    def getWeight(self, nbr):
        return self.connectedTo.get(nbr)
      
class Graph:
  
    def __init__(self):
        self.vertList = {}
        self.numVertices = 0
        
    def addVertex(self, key):
        self.numVertices += 1
        newVertex = Vertex(key)
        self.vertList[key] = newVertex
        return newVertex  
      
    def getVertex(self, key):
        return self.vertList.get(key)
      
    def __contains__(self, key):
        return key in self.vertList
      
    def addEdge(self, f, t, weight = 0):
        """
        Add an edge to connect two vertices of t and f with weight
        assuming directed graph
        
        Time complexity of O(1) as adding vertices if they don't 
        exist and then add neighbor
        """
        
        #add vertices if they do not exist
        if f not in self.vertList:
            nv = self.addVertex(f)
        if t not in self.vertList:
            nv = self.addVertex(t)
            
        #then add Neighbor from f to t with weight
        self.vertList[f].addNeighbor(self.vertList[t], weight)
        
    def getVertices(self):
        return self.vertList.keys()
      
    def getCount(self):
        return self.numVertices

if __name__ == '__main__' :    
    # create the graph
    graph = Graph()
    #comprobante = []
    reducido = []
    cont = 0
    with open('list.txt') as f:
        lines = f.readlines()
    for line in lines:
        if '.edges' in line:
            originId = line.split('\\').pop().split('.').pop(0)
            
            #comprobante.append(originId)
            graph.addVertex(originId)
            with open(line[:-1]) as f2:
                allData = f2.readlines()
            for data in allData:
                relationLine = data.split()
                idX = relationLine[0]
                idY = relationLine[1]
                
                #comprobante.append(idX)
                #comprobante.append(idY)
                
                #graph.add_node(idX)
                #graph.add_node(idY)

                graph.addEdge(originId, idX)
                graph.addEdge(idX, idY)

                
                #reducido = set(comprobante)
                #if(cont == 10000):
                    #break
            cont = cont + 1
            print('Leido el archivo numero', cont)
            print('The nodes and edges in the graph are:')
            print(graph.getCount())
            #print('The nodes and edges in the list are:')
            #print(len(reducido))
        #if(cont == 10000):
            #break

    # create the nodes
    #print('The nodes and edges in the graph are:')
    #print(graph.get_number_of_nodes())
    #print('The nodes and edges in the list are:')
    #print(len(reducido))
    #graph.printNodes()
    ##print(graph)
    #print()
    # print children of node C
    #print('Nodes connected to C are:')
    #for i in graph.children_of(node_c):
        #print(i)