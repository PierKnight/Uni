from threading import Thread,RLock,Lock
from time import sleep

'''
    Classe Astratta Stampa. StampaNonsafe e Stampadisciplinata ne sono rispettivamente figlia e nipote
'''
class Stampa:
    def __init__(self):
        pass
    def stampa(self,c,l):
        pass
    def stampaStriscia(self,c):
        pass
 
#
# Esempio di uso non sincronizzato delle funzioni di stampa
#  
class StampaNonsafe(Stampa):
    def __init__(self):
        super().__init__()

    def stampa(self, c, l):
        for i in range(0,l+1):
            print(c, end='', flush=True)
            #sleep(0.01)
        print('')
    
    def stampaStriscia(self,c):
        self.stampa(c,50)
    
 
class StampaDisciplinata(StampaNonsafe):

    __PRINTS = 2
    def __init__(self):
        super().__init__()
        #con questo posso contare il numero corrente di stamper per thread
        self.count = 0
        #
        # RLock è simile a Lock ma RIENTRANTE: può essere acquisito più volte consecutive dallo stesso thread
        #
        self.lock = RLock()
        

    def stampa(self, c, l):


        #il primo thread che arriva qui acquisisce il lock
        #gli altri che lo trovano preso entrano in stato di attesa
        self.lock.acquire()
    
        #se il count è > 0 vuol dire che il thread ha già il lock e sta stampando
        #quindi ulteriori acquire devono essere rilasciati subito
        #visto che a quando pare gli acquire RLcock si stackano
        if(self.count > 0):
            self.lock.release()
        super().stampa(c,l)


        self.count += 1
        #print(self.count,flush=True)

        #fino a quanto il count non arriva a PRINTS il thread che ha il lock sarà l'unico ad usare il print
        if(self.count > self.__PRINTS):
            #dopo aver realizzato le stampe viene rilasciata il lock ed adesso un thread in wait procederà con le sue stampe
            #ovviamente è necessario resettare il count per il prossimo thread che stampa
            self.count = 0
            
            #for i in range(self.__PRINTS + 1):
            self.lock.release()


class StampatoreDiChar(Thread):

    def __init__(self,s,char):
        super().__init__()
        self.st = s
        self.char = char
    
    def run(self):
        while True:
            sleep(0.6)
            st.stampaStriscia(self.char)
#
# Si può costruire st come StampaNonsafe o come StampaDisciplinata e verificare la differenza
#
#st = StampaNonsafe()
st = StampaDisciplinata()

chars = ['e','b','c']

for i in range(len(chars)):
    printer = StampatoreDiChar(st,chars[i])
    printer.start()

print("Main Terminato")
 
