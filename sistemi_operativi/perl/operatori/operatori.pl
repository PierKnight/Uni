#!/usr/bin/perl
#LISTA DI OPERATORI DI PERL

#abbiamo i classici operatori binari (contesto numero!)
#perl convertirà gli argomenti degli operatori in interi
#OPERATORI: +,-,/,*,** += , -= etc

$numero1 = "1";
$numero2 = "4";


open (TEST,"seees.txt");

#perl  nel contesto di somma converte le stringhe in numeri!
print "SOMMA DEI DUE NUMERI: " . ($numero1 + $numero2) . "\n";


@array = ("e1","e2");
print "Totale Elementi " . @array . "\n";

#poter comporre un array di certi elementi pescandoli attraverso un array di index
@sos = (0);
print @array[@sos];