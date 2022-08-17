#!/usr/bin/python3


from threading import Thread


class Test(Thread):
    def __init__(self, name):
        super().__init__()
        self.name = name

    
    def run(self):
        print("CIAO %s" % self.name)


for i in range(25):
    test = Test("ciao%s" % i)
    test.start()