import os
from threading import Event
from itertools import combinations

allDirections = []
class Vertex:
  
    def __init__(self, key):
        self.id = key
        #self.connectedTo = {} si queremos con pesos
        self.connectedTo = []
        self.features = []
        self.featNames = {}
        self.circles = {}
        
    def addNeighbor(self, nbr, weight = 0):
        #self.connectedTo[nbr] = weight
        self.connectedTo.append(nbr)

        
    def __str__(self):
        #return f"{str(self.id)} connected to: {str([x.id for x in self.connectedTo])}"
        return f"{str(self.id)} connected to: {str([x for x in self.connectedTo])}"
    
    #def getOnlyIdsInAList(self):
        #return [x.id for x in self.connectedTo]
    
    def getCircles(self):
        return self.circles

    def setCircles(self, circles):
        self.circles = circles
    
    def getConnections(self):
        return [int(x.id) for x in self.connectedTo]
        #return self.connectedTo.keys()

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
        self.justAdjacencyList = {}
        
    def addVertex(self, key):
        if(key not in self.vertList or len(self.vertList) == 0):
            self.numVertices += 1
            newVertex = Vertex(key)
            self.vertList[key] = newVertex
            return newVertex  
    
    def getVertex(self, key):
        return self.vertList.get(key)
    
    def getJustAdjacencyList(self):
        for id in self.getUsers():
            vert = self.getVertex(id)
            #print(vert.id)
            #print(vert.getConnections())
            #Event().wait(5)
            self.justAdjacencyList[int(vert.id)] = vert.getConnections()
        return self.justAdjacencyList
    
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
        self.vertList[t].addNeighbor(self.vertList[f], weight)
        
    def getVertices(self):
        return self.vertList.keys()
    
    def getUsers(self):
        return self.vertList

    def getCount(self):
        return self.numVertices
    
    def getCountEdges(self):
        return self.numEdges

def printAllPathsUtil(graph, u, d, visited, path):
    # Mark the current node as visited and store in path
    visited[u]= True
    path.append(u)

    # If current vertex is same as destination, then print
    # current path[]
    if u == d:
        print (path)
    else:
        # If current vertex is not destination
        # Recur for all the vertices adjacent to this vertex
        for i in graph[u]:
            if visited[i]== False:
                printAllPathsUtil(graph, i, d, visited, path)
    # Remove current vertex from path[] and mark it as unvisited
    path.pop()
    visited[u]= False
  
# Prints all paths from 's' to 'd'
def printAllPaths(graph, s, d):

    try:
        # Mark all the vertices as not visited
        #vis =[False]*(len(graph))
        visited = {}

        for i in graph:
            visited[i] = False

        # Create an array to store paths
        path = []

        # Call the recursive helper function to print all paths
        printAllPathsUtil(graph, s, d, visited, path)
    except:
        return
    

def longestPath(graph):
    newGraph = graph.getJustAdjacencyList()
    printAllPaths(newGraph, 116374117927631468606, 101765416973555767821)

if __name__ == '__main__' :    
    graph = Graph()
    comprobante = []
    reducido = []
    cont = 0
    consoleOption = -1
    while(consoleOption != 9):
        os.system ("cls") 
        print('Que dese hacer?')
        print('================================')
        print('0. Cargar grafo')
        print('1. Respuesta a la pregunta 1')
        print('2. Respuesta a la pregunta 2')
        print('3. Respuesta a la pregunta 3')
        print('4. Respuesta a la pregunta 4')
        print('5. Respuesta a la pregunta 5')
        print('6. Respuesta a la pregunta 6')
        print('7. Otros datos')
        print('9. Salir')
        consoleOption = int(input("Opcion: "))
        if consoleOption == 0:
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
                    print('Leido el conjunto de archivos numero: ', cont)
                    comprobante = list(set(comprobante))
                    reducido = list(combinations(comprobante, 2))
                    allDirections.append(reducido)
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
        if consoleOption == 1:
            print('El numero total de usuarios en la red es de:')
            print(graph.getCount())
            input("Presione la tecla enter para continuar ")
        if consoleOption == 2:
            print('El numero de conexiones en la red es de:')
            print(graph.getCountEdges())
            input("Presione la tecla enter para continuar ")

        if consoleOption == 3:
            #print(longestPath(graph.getUsers(), graph.getCount()))
            print('La distancia maxima entre dos usuarios cualquiera de la red es de:')

            longestPath(graph)
            input("Presione la tecla enter para continuar ")

        if consoleOption == 4:
            print('La distancia promedio entre dos usuarios de la red es de:')
            input("Presione la tecla enter para continuar ")


        if consoleOption == 5:
            print('La cantidad de componentes fuertemente conexos en la red es de:')
            input("Presione la tecla enter para continuar ")


        if consoleOption == 6:
            print('El Clique mas grande que se encontro en el grafo fue de:')
            input("Presione la tecla enter para continuar ")


        if consoleOption == 7:
            print('The features of 101738342045651955119 are:')
            print(graph.getVertFeatures('101738342045651955119'))
            print('The features names of 101738342045651955119 are:')
            print(graph.getVertFeaturesNames('101738342045651955119'))
            print('Circles of user 100129275726588145876: ')
            #print(graph.getUserCircles('100129275726588145876'))
            input("Presione la tecla enter para continuar ")

        if consoleOption == 9:
            print('Eso fue todo, Gracias!')
            input("Presione la tecla enter para continuar ")
            

        
    # create the nodes
    
    #print('The number of edges in the graph are:')
    #print(graph.getCountEdges())
    #print('The number of list are:')
    #print(len(comprobante))
    
