#!/usr/bin/perl

#modificatori perl 

my $testo = "questo è un testo con la email pier.altimari@libero.it";


#G: trova ogni evenienza di quell'espressione regolare
if($testo =~ /e/g)
{

}

#s sostituzione s/<quello che cerca>/<la sostituzione>/g #le variabili \1, \2 ... sono i vari match trovati
#RICORDA PER USARE il \1 E NECESSARIO AVERE IL GRUPPO!!!!!

$testo =~ s/(\w|è)/\[\1\]/g;

print $testo;


#esiste anche la funzione <tr> ovvero traslitterazione per sostituire lettera per lettera

my $prova = "CIAO IO SONO UN MESSAGGIO";

$prova =~ tr/AEO/STD/;

print "$prova\n";

#FUNZIONE SPLIT dato un separatore definito con regex ed una stringa separa ques'ultima in più parti dentro l'array ritornato

my @split = split(/e/, "preova");

print $split[0];