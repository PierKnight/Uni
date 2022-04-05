#!/usr/bin/perl

$stringaA = <STDIN>;
chomp($stringaA);

$stringaB = <STDIN>;
chomp($stringaB);

$conc = $stringaA . $stringaB;

print "STRINGA CONCATENATA: $conc\n";

print "LUNGHEZZA STRINGA: " . length($conc) . "\n";


$meta = int(length($conc) / 2);
print "SECONDA META': " . substr($conc,$meta,length($conc) - $meta) . "\n";






