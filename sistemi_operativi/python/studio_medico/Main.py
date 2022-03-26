from multiprocessing import Condition, RLock
from random import randint, randrange
from threading import Thread
from queue import Queue
from time import sleep
from random import randrange
class SalaDiAttesa:

    def __init__(self):
        self.queueMedico = Queue()
        self.queueAlta = Queue()
        self.queueBassa = Queue()
        self.lock = RLock()
        self.cond = Condition()

    def getPaziente(self):

        with self.lock:
            while self.queueAlta.empty() and self.queueBassa.empty():
                self.cond.wait()
            if not self.queueAlta.empty():
                malato = self.queueAlta.get()
                return malato
            elif not self.queueBassa.empty():
                malato = self.queueBassa.get()
                return malato
            


class Segretaria(Thread):

    def __init__(self,salaAttesa):
        super().__init__()
        self.salaAttesa = salaAttesa


    def run(self):
        while(True):
            sleep(1)
            print("Aspetto un Malato")
            if not self.salaAttesa.queueAlta.empty():
                malato = self.salaAttesa.queueAlta.get()
                print(f"Ho dato la ricetta alta a {malato.nome}")
            elif not self.salaAttesa.queueBassa.empty():
                malato = self.salaAttesa.queueBassa.get()
                print(f"Ho dato la ricetta plebeo a {malato.nome}")
            print("neiuwhrkuar")

class Medico(Thread):

    def __init__(self,salaAttesa):
        super().__init__()
        self.salaAttesa = salaAttesa


    def run(self):
        while(True):
            sleep(1)

            print("Medico: Aspetto un Malato")
            malato = self.salaAttesa.queueMedico.get()
            print(f"Medico: Ho Ispezionato malato {malato.nome}")

            if randint(0,1) == 0:
                print(f"Medico: Ho dato ricetta a {malato.nome}")
                self.salaAttesa.queueAlta.put(malato)

class Malato(Thread):

    def __init__(self,salaAttesa,nome):
        super().__init__()
        self.salaAttesa = salaAttesa
        self.nome = nome

    def run(self):
        #print("Tento di mettermi in attesa alta")
        #if randint(0,2) == 0:
        #    self.salaAttesa.queueBassa.put(self)
        #else:
        #    self.salaAttesa.queueAlta.put(self)


attesa = SalaDiAttesa()

for i in range(4):
    malato1 = Malato(attesa, f"Gianni{i}")
    malato1.start()


segretaria = Segretaria(attesa)
medico = Medico(attesa)


segretaria.start()
medico.start()











