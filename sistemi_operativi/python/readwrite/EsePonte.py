
import random
from threading import RLock,Condition, Thread
from time import sleep

class Ponte:

    

    def __init__(self):
        self.lock = RLock()
        self.condition = Condition(self.lock)
        self.max = 3
        self.turisti = 0
        self.waiting = [0,0]
        self.prevDir = 0
        self.ripetizioni = 0
        
  
    def acquireAuto(self,dir):
        self.lock.acquire()
        self.waiting[dir] += 1
        while ((self.turisti != 0 and self.prevDir != dir)  or (dir == self.prevDir and self.ripetizioni >= self.max and self.waiting[1 - dir] > 0) or self.turisti > 1):
            self.condition.wait()

        self.turisti += 1

        if(self.prevDir != dir):
            self.prevDir = dir
            self.ripetizioni = 0
        
        self.ripetizioni += 1

        self.waiting[dir] -= 1

        self.lock.release()

    def releaseAuto(self):
        self.lock.acquire()
        self.turisti -= 1
        if self.turisti == 0:
            self.condition.notifyAll()
        self.lock.release()

class AutoMare(Thread):

    def __init__(self,ponte):
        super().__init__()
        self.ponte = ponte

    def run(self):
        
        #sleep(random.random())
        print(f"Turista Mare {self.name} prova ad attraversare",flush=True)
        self.ponte.acquireAuto(0)
        print(f"Turista Mare {self.name} sta attraversando",flush=True)
        self.ponte.releaseAuto()
        print(f"Turista Mare {self.name} ha attraversato",flush=True)

class AutoMontagna(Thread):

    def __init__(self,ponte):
        super().__init__()
        self.ponte = ponte

    def run(self):
        
        #sleep(random.random())
        print(f"Turista Montagna {self.name} prova ad attraversare",flush=True)
        self.ponte.acquireAuto(1)
        print(f"Turista Montagna {self.name} sta attraversando",flush=True)
        self.ponte.releaseAuto()
        print(f"Turista Montagna {self.name} ha attraversato",flush=True)


ponte = Ponte()

for i in range(3):
    turMar = AutoMare(ponte)
    turMar.start()

for i in range(3):
    montT = AutoMontagna(ponte)
    montT.start()



        






            

            




        
    
        