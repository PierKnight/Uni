#!/usr/bin/perl

sub somma
{
    return $_[0] + $_[1];
}
sub differenza
{
    return $_[0] - $_[1];
}
sub moltiplicazione
{
    return $_[0] * $_[1];
}
sub divisione
{
    return $_[0] / $_[1];
}



$numero_1 = @ARGV[0];
$numero_2 = @ARGV[1];

print "SOMMA:" . somma($numero_1,$numero_2) . "\n";
print "DIFFERENZA:" . differenza($numero_1,$numero_2) . "\n";
print "MOLTIPLICAZIONE:" . moltiplicazione($numero_1,$numero_2) . "\n";
print "DIVISIONE:" . divisione($numero_1,$numero_2) . "\n";
