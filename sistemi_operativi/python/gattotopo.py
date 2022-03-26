import random, time
from threading import Thread, Lock
from sys import version


class Striscia:
    LUNG = 20
    def __init__(self):
        self.striscia=list()
        self.fine = False
        self.dirGatto = 1
        self.topo = random.randint(0,self.LUNG-1)
        self.gatto = random.randint(0,self.LUNG-1)
        self.lock = Lock()
        for i in range(0,self.LUNG):
                self.striscia.append( ' ' )
        self.striscia[self.topo] = '.'
        self.striscia[self.gatto] = '*'
        
    def printStriscia(self):
        self.lock.acquire()
        try:
            print ("|%s|" % ''.join(self.striscia))
            return self.fine
        finally:
            self.lock.release()


    def muoviGatto(self): 
        self.lock.acquire()
        try:
            if (self.fine):
                return True
        
            self.striscia[self.gatto] = ' '
        
            self.gatto += self.dirGatto
            if (self.gatto > self.LUNG-1 or self.gatto < 0): 
                self.dirGatto = -self.dirGatto
                self.gatto += 2 * self.dirGatto
                
            if (self.gatto == self.topo): 
                self.fine = True
                self.striscia[self.gatto] = '@'
                return True
            
            self.striscia[self.gatto] = '*'
            return False
        finally:
            self.lock.release()


    def muoviTopo(self): 
        
        self.lock.acquire()
        try:
            if (self.fine):
                return True
        
            self.striscia[self.topo] = ' '
        
            self.salto = random.randint(-1,1)
            if (self.topo + self.salto >= 0 and self.topo + self.salto < self.LUNG):
                self.topo = self.topo + self.salto
        
            if (self.gatto == self.topo):
                self.fine = True
                self.striscia[self.topo] = '@'
                return True
            
        
            self.striscia[self.topo] = '.'
        
            return False
        finally:
            self.lock.release()


class Display(Thread):


    def __init__(self,s):
        Thread.__init__(self)
        self.striscia = s
        
    def run(self):
        print ("First run Display")
        while (not striscia.printStriscia()):
            time.sleep(0.020)
        print ("Il topo ha fatto la fine del topo")
    
class Gatto(Thread):

    def __init__(self,s):
        Thread.__init__(self)
        self.striscia = s

    def run(self):
        print ("First run Gatto")
        while (not striscia.muoviGatto()):
            time.sleep(0.100)

class Topo(Thread):

    def __init__(self,s):
        Thread.__init__(self)
        self.striscia = s

    def run(self):
        print ("First run Topo")
        while (not striscia.muoviTopo()):
            time.sleep(0.050)



print ("Start Gatto & Topo versione basic")
print ("Python version %s" % version)
striscia = Striscia()
jerry = Topo(striscia)
tom = Gatto(striscia)
display = Display(striscia)
print ("Created")
display.start()
jerry.start()
tom.start()
print ("Started")
time.sleep(10)