#!/usr/bin/perl


$A = "rkerere";

$B = "rrndthkerl";


$C = $A . $B;


$len = length($C);

print "lunghezza: " . $len . "\n";


print "Seconda Meta: " . substr($C,int($len / 2 + 0.99), $len / 2) . "\n";



$test = "jrkearkfnffwerwtrw";


$totaleOccorenze = 0;

for($test =~ /f/g)
{
    $totaleOccorenze += 1;
}


