
from threading import RLock,Condition, Thread
from time import sleep
import random

class CustomBarrier:
    def __init__(self,amount):
        self.lock = RLock()
        self.condition = Condition(self.lock)
        self.amount = amount
        self.count = 0

    
    def wait(self):

        with self.lock:
            print("Arrivato un nuovo thread")
            self.count += 1
            while(self.count < self.amount):
                self.condition.wait()
            self.condition.notifyAll()
            #self.count = 0
            
    def reset(self):
        self.count = 0



class Test(Thread):

    def __init__(self,barrier):
        super().__init__()
        self.barrier = barrier

    def run(self):
        sleep(random.random() * 2)
        barrier.wait()
        print("TES")



barrier = CustomBarrier(3)

for i in range(3):
    test = Test(barrier)
    test.start()
            

