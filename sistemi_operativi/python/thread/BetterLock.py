
from threading import RLock,Condition, Thread
from time import sleep


class BetterLock:
    
    def __init__(self):
        self.__lock = RLock()
        self.__cond = Condition(self.__lock)
        self.__waitingThreads = 0
        self.locked = False

    def getWaitingThreads(self):
        with self.__lock:
            return self.__waitingThreads
    
    def acquire(self):
        with self.__lock:
            self.__waitingThreads += 1
            while (self.locked):
                self.__cond.wait()
            self.locked = True
            self.__waitingThreads -= 1
    
    def release(self):
        with self.__lock:
            self.locked = False
            self.__cond.notify()


lock = BetterLock()

class Test(Thread):
    def __init__(self,lock):
        super().__init__()
        self.lock = lock
    

    def run(self):
        lock.acquire()
        sleep(5)
        lock.release()


for i in range(5):
    thread = Test(lock)
    thread.start()


while(True):
    print(f"Numeri Thread in wait: {lock.getWaitingThreads()}")
    sleep(1)
