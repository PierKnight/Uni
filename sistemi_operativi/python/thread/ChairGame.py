from threading import Thread,RLock
from time import sleep
from random import randrange

class Posto:
    def __init__(self):
        self.__occupato = False
        self.lock = RLock()

    def isOccupato(self):
        return self.__occupato
      
    def checkAndOccupa(self):
        with self.lock:
            if not self.__occupato:
                self.__occupato = True
                return True
            else:
                return False
class Partecipante(Thread):
    def __init__(self,posti):
        super().__init__()
        self.posti = posti

    def run(self):
        sleep(randrange(100) / 100)
        for i in range(len(self.posti)):
            if(self.posti[i].checkAndOccupa()):
                print("Sono il thread %s sono nel posto %d" % (self.getName(),i))
                return
        print( "Sono il Thread %s. NO SEDIA" % self.getName())

class Display(Thread):
    def __init__(self,posti):
        super().__init__()
        self.posti = posti


    def run(self):
        
        while(True):
          sleep(2)
          for i in range(len(self.posti)):
            if self.posti[i].isOccupato():
                print("*",end = "",flush= True)
            else:
                print("-",end = "",flush= True)
          print("\n")

NUMERO_POSTI = 100

posti = [Posto() for i in range(NUMERO_POSTI)]

for i in range(NUMERO_POSTI + 1):
    part = Partecipante(posti)
    part.start()

DISPLAY = Display(posti)
DISPLAY.start()





