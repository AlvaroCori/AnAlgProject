import os
from itertools import combinations

allDirections = []
allLenDirections = []

### Clase Vertex, donde se almacenara la informacion importante de cada usuario.
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
        return f"{str(self.id)} connected to: {str([x for x in self.connectedTo])}"
    
    def getCircles(self):
        return self.circles

    def setCircles(self, circles):
        self.circles = circles
    
    def getConnections(self):
        return [int(x.id) for x in self.connectedTo]

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

### Clase Graph, donde se almacenara la lista de vertices en un diccionario y se tendran las funciones de agregar conexiones, entre otras mas
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
            self.justAdjacencyList[int(vert.id)] = vert.getConnections()
        return self.justAdjacencyList
    
    def __contains__(self, key):
        return key in self.vertList
    
    def setUserCircles(self, id, circles):
        if(self.__contains__(id)):
            self.vertList[id].setCircles(circles)
            for i in circles:
                if(not self.__contains__(i)):
                    self.addVertex(i)
            
    def getUserCircles(self, id):
        return self.vertList[id].getCircles()
    
    def setVertFeatures(self, id, features):
        if(self.__contains__(id)):
            self.vertList[id].setFeatures(features)
        else:
            self.addVertex(id)
    
    def getVertFeatures(self, id):
        if(self.__contains__(id)):
            return self.vertList[id].getFeatures()
        else:
            self.addVertex(id)

    def setVertFeaturesNames(self, id, featuresNames):
        if(self.__contains__(id)):
            self.vertList[id].setFeaturesNames(featuresNames)
        else:
            self.addVertex(id)
    
    def getVertFeaturesNames(self, id):
        return self.vertList[id].getFeaturesNames()

    def addEdge(self, f, t, weight = 0):
        #Se agregan los vertices encaso de que no existan
        if f not in self.vertList:
            nv = self.addVertex(f)
        if t not in self.vertList:
            nv = self.addVertex(t)
        self.numEdges += 1
        #Finalmente se agregan las conexiones, de f a t y t a f para que el grafo sea no dirigido
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

### Algoritmos usados para la pregunta 3 donde es un DFS, que busca los caminos a traves de los nodos adyacentes 
def findPath(graph, u, d, visited, path):
    visited[u]= True
    path.append(u)
    if u == d:
        #print (path)
        allDirections.append(path)
        allLenDirections.append(len(path))
    else:
        # Recur for all the vertices adjacent to this vertex
        for i in graph[u]:
            if visited[i]== False:
                findPath(graph, i, d, visited, path)
    # Remove current vertex from path[] and mark it as unvisited
    path.pop()
    visited[u]= False

def findAllPathsBetween2users(graph, s, d):
    try:
        visited = {}
        for i in graph:
            visited[i] = False
        path = []
        findPath(graph, s, d, visited, path)
    except:
        return

def avg(lst):
    return sum(lst) / len(lst)

def longestPath(graph, s, d):
    newGraph = graph.getJustAdjacencyList()
    findAllPathsBetween2users(newGraph, int(s), int(d))
    return max(allLenDirections)

### Intento de algoritmo de la 4  
def averagePath(graph, s, d):
    newGraph = graph.getJustAdjacencyList()
    findAllPathsBetween2users(newGraph, int(s), int(d))
    return avg(allLenDirections)

if __name__ == '__main__' :    
    graph = Graph()
    comprobante = []
    reducido = []
    cont = 0
    consoleOption = -1
    ### MENU
    while(consoleOption != 9):
        os.system ("cls") 
        print('Que dese hacer?')
        print('================================')
        print('0. Cargar grafo')
        print('1. Respuesta a la pregunta 1')
        print('2. Respuesta a la pregunta 2')
        print('3. Respuesta a la pregunta 3')
        print('4. Respuesta a la pregunta 4')
        print('7. Otros datos')
        print('9. Salir')
        consoleOption = int(input("Opcion: "))
        if consoleOption == 0:
            ### Lectura del archivo list.txt, donde se encuentran el resto de direcciones de los otros archivos
            with open('list.txt') as f:
                lines = f.readlines()
            for line in lines:
                ### originId es el id del archivo que se esta leyendo
                originId = line.split('\\').pop().split('.').pop(0)
                ### Lectura de las direcciones dentro del archivo list.txt
                ### Lectura y alamcenamiento de los .circles, se guardan en un diccionario de igual manera que los otros
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
                ### Lectura y almacenamiento de los .edges, se agregaron las conexiones de nodeId -> idX, idX -> idY
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
                    #reducido = list(combinations(comprobante, 2))
                    #allDirections.append(reducido)
                ### Lectura y almacenamiento del archivo egofeat, que contiene las caracteristicas del usuario con el id del archivo
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
                ### Lectura y almacenamiento de los feat de todos los usuarios creados del archivo .edge
                ### En vez de guardar toda la lista de 1 y 0, se guarda solo la posicion donde se encuentren los 1
                ### Esta parte es distinta, debido a que featnames tambien contiene feat, por lo que en la siguiente linea solo toma en cuenta los archivos que terminen  en .feat
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
                ### Lectura y almacenamiento de los featnames basandose en las caracteristicas previamente recibidas en el .feat
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
            src = input('Ingrese un usuario: ')
            dst = input('Ingrese el siguiente usuario: ')
            print('La distancia maxima entre el usuario ' + src + ' y el usuario ' + dst + ' en la red es de:')
            print(longestPath(graph, src, dst), 'usuarios, incluyendo el usuario inicio y fin')
            input("Presione la tecla enter para continuar ")

        if consoleOption == 4:
            src = input('Ingrese un usuario: ')
            dst = input('Ingrese el siguiente usuario: ')
            print('La distancia promedio entre el usuario ' + src + ' y el usuario ' + dst + ' en la red es de:')
            print(averagePath(graph, src, dst), 'nodos, incluyendo el nodo inicio y nodo destino')
            input("Presione la tecla enter para continuar ")

        if consoleOption == 7:
            print('Las posiciones de los features de 101738342045651955119 son:')
            print(graph.getVertFeatures('101738342045651955119'))
            print('Los nombres de los features de 101738342045651955119 son:')
            print(graph.getVertFeaturesNames('101738342045651955119'))
            #print('Circles of user 100129275726588145876: ')
            #print(graph.getUserCircles('100129275726588145876'))
            input("Presione la tecla enter para continuar ")

        if consoleOption == 9:
            print('Eso fue todo, Gracias!')
            input("Presione la tecla enter para continuar ")
    
