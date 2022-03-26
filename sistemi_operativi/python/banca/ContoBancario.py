

import re
from threading import RLock,Condition
from typing import final

class ContoBancario:
    def __init__(self):
        self.saldo = 0
        self.transazioni = []
        self.lock = RLock
        self.cond = Condition(self.lock)
        self.operating = False


    def getSaldo(self):
        with self.lock:
            return self.saldo



class Transazione:
    def __init__(self,contoA,contoB,somma):
        self.contoA = contoA
        self.contoB = contoB
        self.somma = somma