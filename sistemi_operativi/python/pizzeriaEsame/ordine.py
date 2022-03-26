

class Ordine:
    def __init__(self,tipo,quantita):
        self.__tipo = tipo
        self.__quantita = quantita
    
    def getTipo(self):
        return self.__tipo

    def getQuantita(self):
        return self.__quantita

    