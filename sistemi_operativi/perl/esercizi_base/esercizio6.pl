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
for (1..2)





