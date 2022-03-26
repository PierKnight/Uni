
from random import randint
from threading import Lock,Thread,Barrier
from multiprocessing import RLock, cpu_count
from time import sleep


class VectorWorker(Thread):

    def __init__(self,calcolatore,barrier,result):      
        super().__init__()
        self.calcolatore = calcolatore
        self.barrier = barrier
        self.result = result

    
    def run(self):

        nextNumber = self.calcolatore.getNextNumber()


        totaleCalcoli = 0
        
        while(nextNumber != -1):
            self.result[nextNumber] = self.calcolatore.getOperationResult(self.calcolatore.vectorA[nextNumber],self.calcolatore.vectorB[nextNumber])
            totaleCalcoli += 1
            nextNumber = self.calcolatore.getNextNumber()

        
        print(f"Il Thread {self.getName()} ha finito con totale calcoli {totaleCalcoli}!")

        self.barrier.wait()



class CalcolatoreParallelo:
    def __init__(self,vectorA,vectorB):
        self.vectorA = vectorA
        self.vectorB = vectorB
        self.currentNumber = 0
        self.lock = RLock()

        if(len(self.vectorA) == 0 or len(self.vectorB) == 0):
            raise Exception("Uno dei due vettori è di lunghezza zero!")

        if(len(self.vectorA) != len(self.vectorB)):
            raise Exception("I Vettori non possono essere di lunghezza diversa!")
        
    

    #ottengo il prossimo index dell'array che bisogna calcolare
    #-1 se arrivo alla lunghezza del vettore
    def getNextNumber(self):
        with self.lock:
            if(self.currentNumber >= len(self.vectorA)):
                return -1
            numb = self.currentNumber
            self.currentNumber += 1
            return numb

    
    def getOperationResult(self,a,b):
        pass

    def getResult(self):

        numCore = cpu_count()

        barrier = Barrier(numCore + 1)
        resultVector = [0 for i in range(len(self.vectorA))]


        for i in range(numCore):
            worker = VectorWorker(self,barrier,resultVector)
            worker.start()

        barrier.wait()
        return resultVector


class SommaParallela(CalcolatoreParallelo):

    def __init__(self,vectorA,vectorB):
        super().__init__(vectorA,vectorB)

    def getOperationResult(self,a,b):
        return a + b 

class SottrazioneParallela(CalcolatoreParallelo):

    def __init__(self,vectorA,vectorB):
        super().__init__(vectorA,vectorB)

    def getOperationResult(self,a,b):
        return a - b 

class Operazioni:

    def __init__(self):
        pass

    def somma(self,vectorA,vectorB):
        somma = SommaParallela(vectorA,vectorB)
        return somma.getResult()

    def sottrai(self,vectorA,vectorB):
        sottrazione = SottrazioneParallela(vectorA,vectorB)
        return sottrazione.getResult()

lenght = 500000

vectorA = [3 for i in range(lenght)]
vectorB = [3 for i in range(lenght)]

operazione = Operazioni()

result = operazione.somma(vectorA,vectorB)

for i in range(4):
    print(result[i],end = " ")
print()





     




