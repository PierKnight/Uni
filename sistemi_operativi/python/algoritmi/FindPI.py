
from threading import RLock, Thread
import random
from time import sleep


class PointsThread(Thread):
    def __init__(self,finder):
        super().__init__()
        self.finder = finder

    

    def run(self):
        while(True):
            randomX = random.uniform(0,self.finder.raggio * 2)
            randomY = random.uniform(0,self.finder.raggio * 2)

            
          
            if (randomX - self.finder.raggio) * (randomX - self.finder.raggio) + (randomY - self.finder.raggio) * (randomY - self.finder.raggio) <= self.finder.raggio * self.finder.raggio:
                self.finder.lock.acquire()
                self.finder.circlePoints += 1
                self.finder.lock.release()

            self.finder.sLock.acquire()
            self.finder.totalPoints += 1
            self.finder.sLock.release()

            





class PIFinder(Thread):

    def __init__(self,raggio,maxTries):
        super().__init__()
        self.totalPoints = 0
        self.circlePoints = 0
        self.raggio = raggio
        self.lock = RLock()
        self.sLock = RLock()
        self.maxTries = maxTries
    
    def getCurrentPi(self):
        if self.totalPoints == 0:
            return 0
        return self.circlePoints / self.totalPoints * 4

    def run(self):
        while(True):
            sleep(0.1)
            self.lock.acquire()
            self.sLock.acquire()
            print(self.getCurrentPi())
            self.lock.release()
            self.sLock.release()
    


finder = PIFinder(1,1)
finder.start()

for i in range(4):
    th = PointsThread(finder)
    th.start()