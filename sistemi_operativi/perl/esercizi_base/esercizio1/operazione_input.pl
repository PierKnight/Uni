#!/usr/bin/perl


if (scalar @ARGV - 2 != 0)
{
    die "è necessario avere due argomenti!!";
}

#print "What is your name?\n";
#$name = <STDIN>;
#chomp($name);
#print "Your name is ",$name,"\n";


$numero_1 = @ARGV[0];
$numero_2 = @ARGV[1];


$somma = $numero_1 + $numero_2;
print "SOMMA: $somma\n";

$differenza = $numero_1 - $numero_2;
print "DIFFERENZA: $differenza\n";

$moltiplicazione = $numero_1 * $numero_2;
print "MOLTIPLICAZIONE: $moltiplicazione\n";

$divisione = $numero_1 / $numero_2;
print "DIVISIONE: $divisione\n";
