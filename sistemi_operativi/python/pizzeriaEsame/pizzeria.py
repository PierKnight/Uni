import queue
from blocking_queue import PizzaBuffer
from ordine import Ordine

class Pizzeria:
    def __init__(self,ordiniSize,pizzeSize):
        self.bufferOrdini = queue.Queue(ordiniSize)
        self.bufferPizza = PizzaBuffer(pizzeSize)

    def putOrdine(self,tipo,quantita):
        ordine = Ordine(tipo,quantita)
        self.bufferOrdini.put(ordine)
        return ordine

    def getOrdine(self):
        return self.bufferOrdini.get()
    
    def putPizze(self,ordine):
        self.bufferPizza.put(ordine)
        
    def getPizze(self,ordine):
        ord = self.bufferPizza.get(ordine)
        return ord
        
            




    