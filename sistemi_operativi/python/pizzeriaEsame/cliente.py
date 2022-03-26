from threading import Thread
from random import randrange
from time import sleep


class Cliente(Thread):
    ID = 0
    def __init__(self,pizzeria):
        super().__init__()
        self.pizzeria = pizzeria
        self.ID = Cliente.ID
        Cliente.ID = Cliente.ID + 1

    def info(self,info):
        print("Cliente %d: %s" % (self.ID,info))
    
    def run(self):
        
        #while(True):
            #decide che ordine fare
            randTipo = randrange(2)
            randQuant = randrange(1,3)
            self.info("Cerco di ordinare La pizza scelta ora")
            
            #effettua ordine (nota può andare in attesa il thread)
            ordine = self.pizzeria.putOrdine(randTipo,randQuant)
            #il cliente aspetta prima di richiedere la pizza
            self.info("Ordine effettuato, ora sleep")
            sleep(randQuant * 6 + randrange(-2,2))
            self.info("aspetto la pizza attivamente")

            #ora il cliente pretende la sua pizza se non c'è il thread va in wait
            self.pizzeria.getPizze(ordine)

            self.info("Ho Avuto la mia pizza!")
            #fine



