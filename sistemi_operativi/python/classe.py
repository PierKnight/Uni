#!/usr/bin/python3

#x = 0 indica che il valore passata ha valore default 0


class MyClass:
    def __init__(self, **kwargs):
        self.x = ""
        if("x" in kwargs):
            self.x = kwargs["x"]
        print("Costruttore MyCall")

    #metodo publico
    def print(self):
        print("Il valore di x è: ",self.x)
    
    #metodo protetto
    def _metodoProtetto(self):
        pass

    #metodo privato
    def __metodoPrivato(self):
        pass
    