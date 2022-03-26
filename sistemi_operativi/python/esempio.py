#!/usr/bin/python3

#è come un vector in cpp
array = []
array.append("eeee")

print("ELE: %a" %(array[0]))

#conversione int in string
#str()

#conversione stringa ad int
#int()

#True e False sono in upper case la prima lettera

#funzione input per prendere valori, come argomento ha una stringa ed indica cosa printare
#di default input prende tutto come una stringa

input("Inserisci un nuovo valore: ")

#Definizione classe
#I metodi sono tutti publici

#Notare che ogni variabile della classe si indica con self.<nome variabile>
class MyClass:
    #def __init__ è il costruttore
    def __init__(self, x = 0):
        print("Costruttore con parametro x")
        self.x = x

    #metodo che stampa X
    def printX(self):
        print("x = %d" %(self.x))
        


