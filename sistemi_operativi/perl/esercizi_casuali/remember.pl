#!/usr/bin/perl


sub somma
{
    $somma = 0;
    for(@_)
    {
        $somma += $_; 
    }
    return $somma;
}

sub differenza
{
    $somma = 0;
    for(@_)
    {
        $somma -= $_; 
    }
    return $somma;
}

print "la somma è " . somma(@ARGV) . "\n";
print "la differenza è " . differenza(@ARGV) . "\n";



$value = <STDIN>;
$somma = $value;
chomp($value);

while($value != -1)
{
    $value = <STDIN>;
    $somma += $value;
}

print "SOMMA = $somma\n";



@lista = qx(ls $ARGV[-1]);

for(@lista)
{
    print "$_\n" if($_  =~ /ciao\w+/);
}

print "TRISTE NIENTE RISULTATO!\n" if(not $lista);
    








