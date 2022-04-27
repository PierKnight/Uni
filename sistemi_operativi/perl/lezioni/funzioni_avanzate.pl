#!/usr/bin/perl

#permette di poter eseguire shell script e l'output inserito in un array qx(<comando>)
my @output = qx(ls -l);
#oppure un'altro modo è usare i backticks 
#il system("<comando>") stampa semplicemente


print "@output";


$index = 0;

for (@output)
{
    print "Linea numero $index: $_";
    $index += 1;
}

#system("clear");


#come fare il sort custom

%mappa_media_studente = (francesco => 19, denise => 20, ianni => 18);

#sort ordina in ordine alfabetico se sono stringhe di default
for (sort keys %mappa_media_studente)
{
    print "Chiave: $_ ----> Valore: $mappa_media_studente{$_}\n";
}

#cmp permette di comparare stringhe
#<=> permette di comparare i numeri

#esempi di sort
#sort {$a cmp $b} // comparo a con b attraverso il metodo cmp
#sort {$b cmp $a} in questo modo ho invertito il sort scambiando a e b
#sort {$a <=> $b} W

#for (sort ... array) permette di fare un for dell'array ordinato secondo un criterio come cmp, <=> etc


#IMPORTANTE si può concatenare sort a più livelli con ||, esempio sort (primo sort) poi se gli elementi sono uguali dopo || si aggiunge un secondo predicate



#---------------FUNZIONI-SPLIT--------------------
$info = "eilrje/mrrerm/ekr/dmerker/sos.txt";

@array_splittato = split("/",$info); #il primo argomento il carattere che separa, il secondo è la stringa, ritorna un array di parole splittate

print "PRIMO ELEMENTO: $array_splittato[0]\n";


#HASH DI ARRAY
# KEY1 => [1,2,3]

#le hash non hanno possibilità normalmente di inserire array ma solo scalari come value;

@array_1 = (1,2,3);
%mappa_array;

#usiamo il riferimento dell'array come value
#con [<array>]
$mappa_array{"sos"} = [@array_1];

#deferenziare un array, si deferenzia con il tipo di variabile e poi nelle graffe il riferimento
#def_array = @{<riferimento>}
#la @ se si usa su un array
#la $ se si usa uno scalar

@def = @{$mappa_array{"sos"}};


#HASH DI HASH
#creazione
$HoH{primaChiave}{francesco} = "ciao 1";
$HoH{primaChiave}{denise} = "ciao 2";

$HoH{secondaChiave}{francesco} = "ciao 11";
$HoH{secondaChiave}{denise} = "ciao 22";

#oppire

%hashofhash = (primaChiave => {francesco => 1},secondaChiave => {francesco => 22});

#regex per sostituire match

$stringa = "ik4,wklj3 rkge lfsos enjwlkwrsosqaQEW";

$stringa =~ s/sos/ses/g;

print $stringa . "\n";





