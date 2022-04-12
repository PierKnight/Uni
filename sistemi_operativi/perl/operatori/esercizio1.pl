#!/usr/bin/perl

%mappa = (A => 1,B => 45, C => 5);

#stampa ordinata dei valori prima come numero poi come stringa

for (sort{$a <=> $b | $a cmp $b} values %mappa)
{
    print $_ . "\n";
}

#aggiunta di 3 valori all'array

$mappa{D} = 45;
$mappa{E} = 10;
$mappa{F} = 1;

for (sort{$a <=> $b | $a cmp $b} values %mappa)
{
    print $_ . "\n";
}
