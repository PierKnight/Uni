#!/usr/bin/python3

from studente import studente
from persona import persona
from esame import esame

pers = persona(cf = "WRF",nome = "Pierluigi",cognome = "Altimari",eta = "22")
pers.print()

es = esame("EEE",10,10)
es.print()

student = studente(eta = 22,cf = "asd",matricola = 154600, nome = "Pierluigi",cognome = "Altimari")
student.print()