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
        self.numEdges = 0
        
    def addVertex(self, key):
        if(key not in self.vertList or len(self.vertList) == 0):
            self.numVertices += 1
            newVertex = Vertex(key)
            self.vertList[key] = newVertex
            return newVertex  
      
    def getVertex(self, key):
        return self.vertList.get(key)
      
    def __contains__(self, key):
        return key in self.vertList
      
    def addEdge(self, f, t, weight = 0):
        #add vertices if they do not exist
        if f not in self.vertList:
            nv = self.addVertex(f)
        if t not in self.vertList:
            nv = self.addVertex(t)
        self.numEdges += 1
        #then add Neighbor from f to t with weight
        self.vertList[f].addNeighbor(self.vertList[t], weight)
        
    def getVertices(self):
        return self.vertList.keys()
      
    def getCount(self):
        return self.numVertices
    def getCountEdges(self):
        return self.numEdges

if __name__ == '__main__' :    
    graph = Graph()
    comprobante = []
    reducido = []
    cont = 0
    with open('list.txt') as f:
        lines = f.readlines()
    for line in lines:
        if '.edges' in line:
            originId = line.split('\\').pop().split('.').pop(0)
            
            comprobante.append(originId)
            graph.addVertex(originId)
            with open(line[:-1]) as f2:
                allData = f2.readlines()
            for data in allData:
                relationLine = data.split()
                idX = relationLine[0]
                idY = relationLine[1]
                
                comprobante.append(idX)
                comprobante.append(idY)

                graph.addEdge(originId, idX)
                graph.addEdge(idX, idY)

            cont = cont + 1
            print('Leido el archivo numero', cont)
            
        comprobante = list(set(comprobante))


    # create the nodes
    print('The number of users in the graph are:')
    print(graph.getCount())
    print('The number of edges in the graph are:')
    print(graph.getCountEdges())
    print('The number of list are:')
    print(len(comprobante))