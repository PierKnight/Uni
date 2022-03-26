#!/usr/bin/python3

import re


class esame:

    def __init__(self,nome,cfu,voto):
        self.nome = nome
        self.cfu = cfu
        self.voto = voto
        
    def print(self):
        print("Nome: %s, CFU: %d, Voto: %d" %(self.nome,self.cfu,self.voto))

    def __eq__(self,other):
        return (self.nome == other.nome and self.cfu == other.cfu)

    def __ne__(self,other):
        return not self == other
    
