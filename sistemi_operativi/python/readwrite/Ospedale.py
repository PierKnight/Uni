import re
from sys import displayhook
from threading import RLock,Condition,Thread
from time import sleep
import random
from queue import Queue

class StanzaOspedale:
    def __init__(self):
        self.lock = RLock()
        self.medicoCond = Condition(self.lock)
        self.visitatoreCond = Condition(self.lock)
        self.totaleMedici = 0
        self.totaleOspiti = 0
        self.displayCond = Condition(self.lock)
    

    def entraVisitatore(self):
        with self.lock:
            while(self.totaleMedici > 0 or self.totaleOspiti > 5):
                self.visitatoreCond.wait()
            self.totaleOspiti += 1
            self.displayCond.notify()

    def esceVisitatore(self):
        with self.lock:
            self.totaleOspiti -= 1
            if(self.totaleOspiti == 0):
                self.medicoCond.notifyAll()
            self.displayCond.notify()

    def entraMedico(self):
        with self.lock:
            while(self.totaleMedici > 0 or self.totaleOspiti > 0):
                self.medicoCond.wait()
            self.totaleOspiti += 1
            self.displayCond.notify()


    def esceMedico(self):
        with self.lock:
            self.totaleMedici -= 1
            self.visitatoreCond.notifyAll()
            self.displayCond.notify()

    def print(self):
        while(True):
            with self.lock:
                self.displayCond.wait()
                
                for i in range(self.totaleOspiti):
                    print("*",end = " ")
                print()
                for i in range(self.totaleMedici):
                    print("O",end = " ")
                print()
                    

class Medico(Thread):

    def __init__(self,stanza,id):
        super().__init__()
        self.stanza = stanza
        self.id = id

    def run(self):
        for i in range(4):
            
            self.stanza.entraMedico()
            sleep(1)  #tempo di lavoro
            self.stanza.esceMedico()
class Ospite(Thread):

    def __init__(self,stanza,id):
        super().__init__()
        self.stanza = stanza
        self.id = id

    def run(self):
        for i in range(4):
            sleep(random.randint(2,4)) 
            self.stanza.entraVisitatore()
            sleep(random.randint(1,2))  #tempo di visita
            self.stanza.esceVisitatore()

class Display(Thread):
    def __init__(self,stanza):
        super().__init__()
        self.stanza = stanza
    
    def run(self):
        stanza.print()



stanza = StanzaOspedale()

display = Display(stanza)
display.start()

for i in range(3):
    medico = Medico(stanza,i)
    medico.start()

for i in range(10):
    ospite = Ospite(stanza,i)
    ospite.start()



