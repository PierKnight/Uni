#!/usr/bin/perl

%rubrica = ();


#inseriamo degli elementi
$rubrica{Pierluigi} = "8374349345";
$rubrica{Piero} = "674349345";
$rubrica{Vincenzo} = "765423344";

for (sort {$a cmp $b || $rubrica{$a} cmp $rubrica{$b}} keys %rubrica)
{
    print "Persona: $_, Numero: $rubrica{$_}\n";
}