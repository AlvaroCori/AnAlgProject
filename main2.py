class Vertex:
  
    def __init__(self, key):
        self.id = key
        self.connectedTo = {}
        self.features = []
        self.featNames = {}
        self.circles = {}
        
    def addNeighbor(self, nbr, weight = 0):
        self.connectedTo[nbr] = weight
        
    def __str__(self):
        return f"{str(self.id)} connected to: {str([x.id for x in self.connectedTo])}"
      
    def getCircles(self):
        return self.circles

    def setCircles(self, circles):
        self.circles = circles
    
    def getConnections(self):
        return self.connectedTo.keys()

    def setFeatures(self, features):
        self.features = features.copy()
    
    def getFeatures(self):
        return self.features
    
    def setFeaturesNames(self, featuresNames):
        self.featNames = featuresNames.copy()
    
    def getFeaturesNames(self):
        return self.featNames
    
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
    
    def setUserCircles(self, id, circles):
        if(self.__contains__(id)):
            self.vertList[id].setCircles(circles)
    
    def getUserCircles(self, id):
        return self.vertList[id].getCircles()
    
    def setVertFeatures(self, id, features):
        if(self.__contains__(id)):
            self.vertList[id].setFeatures(features)
    
    def getVertFeatures(self, id):
        if(self.__contains__(id)):
            return self.vertList[id].getFeatures()

    def setVertFeaturesNames(self, id, featuresNames):
        if(self.__contains__(id)):
            self.vertList[id].setFeaturesNames(featuresNames)
    
    def getVertFeaturesNames(self, id):
        return self.vertList[id].getFeaturesNames()

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
        originId = line.split('\\').pop().split('.').pop(0)
        if '.circles' in line:
            graph.addVertex(originId)
            with open(line[:-1]) as f2:
                allData = f2.readlines()
            circles = {}
            for data in allData:
                circlesLine = data.strip().split()
                id = circlesLine[0]
                users = circlesLine[1:]
                circles[id] = users
            graph.setUserCircles(originId, circles)
            

        if '.edges' in line:
            comprobante.append(originId)
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
        if '.egofeat' in line:
            with open(line[:-1]) as f2:
                allData = f2.readlines()
                for data in allData:
                    dataLine = data.strip().split()
                    features = []
                    posicion = -1
                    try:
                        while True:
                            posicion = dataLine.index('1', posicion + 1)
                            features.append(posicion)
                    except:
                        pass
                    graph.setVertFeatures(originId, features)
        if line[:-1].endswith('.feat'):
            idsFeat = []
            idsFeat.append(originId)
            with open(line[:-1]) as f2:
                allData = f2.readlines()
                for data in allData:
                    dataLine = data.strip().split()
                    id = dataLine[0]
                    if(graph.__contains__(id)):
                        idsFeat.append(id)
                    dataFeatures = dataLine[1:]
                    features = []
                    posicion = -1
                    try:
                        while True:
                            posicion = dataFeatures.index('1', posicion + 1)
                            features.append(posicion)
                    except:
                        pass
                    graph.setVertFeatures(id, features)
        if 'featnames' in line:
            with open(line[:-1]) as f2:
                allData = f2.readlines()
                dictPostFeatNames = {}
                for data in allData:
                    dataLine = data.strip().split()
                    key = int(dataLine[0])
                    feature = dataLine[1]
                    dictPostFeatNames[key] = feature
                for id in idsFeat:
                    listOfFeatNames = {}
                    posFeatNames = graph.getVertFeatures(id)
                    for key in posFeatNames:
                        Allfeature = dictPostFeatNames.get(key)
                        fragmentedFeature = Allfeature.split(':')
                        title = fragmentedFeature[0]
                        description = fragmentedFeature[1]
                        listOfFeatNames[title] = description
                    #print(listOfFeatNames)
                    graph.setVertFeaturesNames(id, listOfFeatNames)

    # create the nodes
    print('The number of users in the graph are:')
    print(graph.getCount())
    print('The number of edges in the graph are:')
    print(graph.getCountEdges())
    print('The number of list are:')
    print(len(comprobante))
    print('The features of 101738342045651955119 are:')
    print(graph.getVertFeatures('101738342045651955119'))
    print('The features names of 101738342045651955119 are:')
    print(graph.getVertFeaturesNames('101738342045651955119'))
    print('Circles of user 100129275726588145876: ')
    #print(graph.getUserCircles('100129275726588145876'))
