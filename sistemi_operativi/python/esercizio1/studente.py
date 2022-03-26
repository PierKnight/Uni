#!/usr/bin/python3

from persona import persona
from esame import esame

class studente(persona):
    def __init__(self,**map):
        super(studente,self).__init__(**map)

        self.matricola = ""
        if("matricola" in map):
            self.matricola = map["matricola"]

    def print(self):
        super().print()
        print("Matricola: %s" % (self.matricola))

    #e not in self.listEsami

    def calcolaMedia(self):
        pass
    def controllaEsame(self):
        pass

    def addEsame(self):
        pass