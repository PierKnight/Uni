

from threading import RLock,Condition, Thread
from random import randint, randrange
from time import sleep


class Slave(Thread):

    def __init__(self,master,x,y,sizeX,sizeY):
        super().__init__()
        self.master = master
        self.x = x
        self.y = y
        self.sizeX = sizeX
        self.sizeY = sizeY

    #questo metodo controlla quente cellule vicine sono vive, utilizzando il "Moore neighborhood"
    def __neightbourAlive(self,x,y):
        count = 0
        for i in range(0,3):
            for j in range(0,3):
                if i != 1 or j != 1:
                    if(self.master.matrix[(self.x + x - 1 + i) % self.master.sizeX][(self.y + y - 1 + j) % self.master.sizeY]):
                        count += 1

        return count


    def run(self):

        print(f"Thread {self.name}: Inizio a lavorare")

        for i in range(self.sizeX):
            for j in range(self.sizeY):
                count = self.__neightbourAlive(i,j)
                isAlive = self.master.matrix[self.x + i][self.y + j]

                #qui le regole applicati solo dei cellular automata ovvero:
                #se una cella ha 3 vicini vivi ne nasce una nuova
                #se ne ha due o 3 una cellula rimane viva
                #negli altri casi muore (se viva ovviamnete)

                if isAlive:
                        self.master.newMatrix[self.x + i][self.y + j] = count == 2 or count == 3 #morte oppure sopravvivenza
                else:
                        self.master.newMatrix[self.x + i][self.y + j] = count == 3 #nascita della cella
        
        #lock utile per poter rendere Thread Save questo codice facendo che solo thread alla volta notifichi il suo completamneto
        with self.master.lock:
            #Segnalo che questo slave ha finito di aggiornare
            print(f"Thread {self.name}: ho finito!")
            self.master.slaveFinish += 1
            self.master.condition.notify()             





class Master(Thread):

    def __init__(self,sizeX,sizeY):
        super().__init__()
        self.sizeX = sizeX #colonne matrice 
        self.sizeY = sizeY #righe matrice
        self.matrix = [] #la matrice corrente 
        self.newMatrix = [] #la matrice cosiddetta di supporto per poter salvare il prossimo stato corrente
        self.lock = RLock() #essenziale per gestire i thread come vedremo tra poco
        self.condition = Condition(self.lock)
        self.slaveFinish = 0 #indica quanto tutti i thread slave hanno finito
        

        for i in range(self.sizeY): #questo genera le matrici nel construttore
            newRow = []
            newRow2 = []
            for j in range(self.sizeX):
                newRow.append(randint(0,1) == 0) #per poter generare una matrice inizialmente casuale
                newRow2.append(False) 
            self.matrix.append(newRow)
            self.newMatrix.append(newRow2)


    #usato per stampare la matrice al momento del completamento del lavoro dei thread slave
    def __print(self):
        for i in range(self.sizeX):
            for j in range(self.sizeY):
                if(self.matrix[i][j]):
                    print("X ",end="",flush=True)
                else:
                    print("- ",end="",flush=True)
            print()
        #print('O ' * self.sizeX,flush=True)
        

    
    def run(self):

        self.__print() #è importante inizializzare il lock ora, cosi da poter garantire una inizializzazione sicura #stampo la matrice all'inizio del loop
        string = input()

        while(not string.__eq__("s")):
            sleep(1)
            with self.lock:
                print("Inizializzo gli slave")
                for i in range(4): #qui inizializziamo in questo caso 4 thread che gestiranno orizzontalmente la matrice
                    slave = Slave(self, i * self.sizeX // 4, 0, self.sizeX // 4,self.sizeY)
                    slave.start()
                #i quattro slave hanno finito!

                #in questo spazio, a livello teorico, senza aver lockato tutto uno slave thread potrebbe finire prima del wait del master
                #causando la perdita del notity!

                print("Aspetto che gli slave finiscano")

                while self.slaveFinish < 4: #qui il master aspetta che tutti gli slave finiscano di processare
                    self.condition.wait()

                print("Gli Slave Hanno finito!")

                #resettare
                self.slaveFinish = 0
                
                #scambio delle matrici cosi da poterle riutilizzare senza doverne instanziare di nuove
                temp = self.matrix
                self.matrix = self.newMatrix
                self.newMatrix = temp
                self.__print()
                string = input()



#si inizializza il master con una certa grandezza di matrice
#meglio utilizzare multipli del numero di thread che lavorano la matrice(in questo caso multipli di 4)
master = Master(16,16)
master.start()

        



    

    

