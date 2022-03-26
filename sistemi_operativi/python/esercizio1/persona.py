#!/usr/bin/python3

class persona:

    def __init__(self,**map):
        self.cf = ""
        self.nome = ""
        self.cognome = ""
        self.eta = 0

        if("cf" in map):
            self.cf = map["cf"]
        if("nome" in map):
            self.nome = map["nome"]
        if("cognome" in map):
            self.cognome = map["cognome"]
        if("eta" in map):
            self.eta = map["eta"]
    
    def print(self):
        print("CF: ",self.cf)
        print("Nome: ",self.nome)
        print("Cognome: ",self.cognome)
        print("Età: ",self.eta)
    
    
