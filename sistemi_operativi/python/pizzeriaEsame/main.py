from pizzaiolo import Pizzaiolo
from pizzeria import Pizzeria
from cliente import Cliente

pizzeria = Pizzeria(2,1)

print("hello")

clienti = [Cliente(pizzeria) for i in range(2)]
pizzaioli = [Pizzaiolo(pizzeria) for i in range(2)]

for i in range(len(clienti)):
    clienti[i].start()

for i in range(len(pizzaioli)):
    pizzaioli[i].start()
