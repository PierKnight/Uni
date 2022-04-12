#!/usr/bin/perl


%mappa = (a => 1, b => 2);
print "VALORE DI A: " . $mappa{a} . "\n";


#inserire 4 elementi nella mappa
$mappa{c} = 5;
$mappa{d} = 5;
$mappa{e} = 5;
$mappa{f} = 5;

#modifico la key a
$mappa{a} = 7;

#controllo se esiste value con key c
print $mappa{c} ? "SI ESISTE UNA CHIAVE C!\n" : "OH NO NON ESISTE UNA CHIAVE C!\n";

#estrazione delle prime due key ed inserirle in un array

#creo un nuovo array con le chiavi della mappa da 1 a 2! (ricorda la mappa è in hash quindi l'ordine non è previsto!)
for ((keys %mappa)[0..1])
{
    print $_ . "\n";
}

#ma potremmo ordinare per avere le chiavi in ordine alfabetico
for ($test = (sort keys %mappa)[0..1])
{
    print $test . "\n";
}

print "Lunghezza Mappa: " . scalar %mappa . "\n";

#rimozione chiave a e b

delete $mappa{a};
delete $mappa{b};

print "Lunghezza Mappa: " . scalar %mappa . "\n";





