

from multiprocessing import RLock
import re
from threading import Thread
from time import sleep

class Contenitore(Thread):

    def __init__(self):
        super().__init__()
        self.totale = 0
        self.shouldPrint = False
        self.lock = RLock()

    def print(self):
        print("Valore totale: ",self.totale,flush=True)

    def run(self):
         pass


class SommatoreThread(Thread):

    def __init__(self,contenitore,valore,maxTimes):
        super().__init__()
        self.contenitore = contenitore
        self.valore = valore
        self.maxTimes = maxTimes
        self.times = 0
    
    def run(self):
        
        self.contenitore.lock.acquire() 
        print("Tocca a ",self.name)   
        while(self.times < self.maxTimes):
            self.contenitore.totale += self.valore
            self.times += 1
        self.contenitore.lock.release()
            
        print("Sommatore n.%s ha finito! somma corrente: %d" % (self.name,self.contenitore.totale),flush=True)
        
        

cont = Contenitore()

sommatore1 = SommatoreThread(cont,5,1000000)
sommatore2 = SommatoreThread(cont,-3,1000000)
sommatore3 = SommatoreThread(cont,1,1000000)


cont.start()
sommatore1.start()
sommatore2.start()
sommatore3.start()
    


