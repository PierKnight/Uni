
from threading import Thread
from time import sleep
from random import randrange

class Pizzaiolo(Thread):
    ID = 0
    def __init__(self,pizzeria):
        super().__init__()
        self.pizzeria = pizzeria
        self.ID = Pizzaiolo.ID
        Pizzaiolo.ID = Pizzaiolo.ID + 1
    
    def info(self,info):
        print("Pizzaiolo %d: %s" % (self.ID,info))

    def run(self):

        while(True):
            self.info("Cerco un ordine...")
            ordine = self.pizzeria.getOrdine()

            self.info("Processo L'ordine..")

            sleep(ordine.getQuantita() * 6 + randrange(-2,2))

            self.info("Cerco di mettere le pizze nel buffer")

            self.pizzeria.putPizze(ordine)
            self.info("Fine!!!")



