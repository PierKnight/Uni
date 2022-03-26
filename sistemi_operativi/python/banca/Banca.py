from cmath import nan
from threading import Condition,RLock
from ContoBancario import ContoBancario,Transazione


class Banca:
    def __init__(self):
        self.conti = {}
        self.lock = RLock


    def getSaldo(self,c):
        if(c in self.conti):
            return self.conti[c].getSaldo()
        return nan

    def trasferisci(self,A,B,N):
        
        with self.lock:

            with A.lock:

                if A.saldo < N:
                    return False

                with B.lock:
                    A.saldo -= N
                    B.saldo += N

                    trans = Transazione(A,B,N)

                    A.transazioni.append(trans)
                    if len(A.transazioni) == 51:
                        A.remove(0)

                    B.transazioni.append(trans)
                    if len(B.transazioni) == 51:
                        B.remove(0)




Banca b              

                
                
            
            

            



            


