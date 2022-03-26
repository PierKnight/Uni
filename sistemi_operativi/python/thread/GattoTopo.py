from multiprocessing import RLock
from random import randrange
from threading import Thread
from time import sleep


class Striscia:
    def __init__(self,lunghezza):
        self.lunghezza = lunghezza
        self.strArray = []
        self.end = False
        self.lock = RLock()
        for i in range(lunghezza):
            self.strArray.append(' ')

    def printStriscia(self):
        self.lock.acquire()
        for i in range(self.lunghezza):
            print(self.strArray[i],end= "",flush= True)
        print('\n',flush=True)
        self.lock.release()

class Entita(Thread):
    def __init__(self,striscia,char):
        super().__init__()
        self.pos = randrange(striscia.lunghezza)
        self.striscia = striscia
        self.char = char
        self.striscia.strArray[self.pos] = self.char
    
    def nextMove(self):
        pass

    def _moveRight(self):
        if self.pos < self.striscia.lunghezza - 1:
           self.striscia.strArray[self.pos] = ' '
           self.pos += 1
           if(self.striscia.strArray[self.pos] != ' '):
               self.striscia.end = True
           self.striscia.strArray[self.pos] = self.char
           return True
        return False
    
    def run(self):
        while(not self.striscia.end):
            sleep(randrange(10) / 10)
            self.striscia.lock.acquire()
            self.nextMove()
            self.striscia.lock.release()
    
    def _moveLeft(self):
        if self.pos > 0:
           self.striscia.strArray[self.pos] = ' '
           self.pos -= 1
           if(self.striscia.strArray[self.pos] != ' '):
               self.striscia.end = True
           self.striscia.strArray[self.pos] = self.char
           return True
        return False
        
        
        


class Gatto(Entita):
    def __init__(self, striscia):
        super().__init__(striscia,"#")
        self.toRight = randrange(2) == 0

    def nextMove(self):
        if(self.toRight):
            if(not self._moveRight()):
                self.toRight = False
        else:
            if(not self._moveLeft()):
                self.toRight = True

class Topo(Entita):
    def __init__(self, striscia):
        super().__init__(striscia, '.')
    
    def nextMove(self):
        ra = randrange(3)
        if ra == 0:
            self._moveRight()
        elif ra == 1:
            self._moveLeft()

class Display(Thread):
    def __init__(self,striscia,gatto,topo):
        super().__init__()
        self.striscia = striscia
        self.gatto = gatto
        self.topo = topo
    
    def run(self):
        while(not self.striscia.end):
            self.striscia.printStriscia()


striscia = Striscia(10)
topo = Topo(striscia)
gatto = Gatto(striscia)

display = Display(striscia,gatto,topo)


topo.start()
gatto.start()
display.start()
