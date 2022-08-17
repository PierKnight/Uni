#!/usr/bin/perl

#esercizio per prendere solo la colonna dei peso dei file e trovare quello più grande

@values = qx(ls -ahl);

my $fileGrosso = "";
my $biggestValue = 1000000;

for(1..scalar @values)
{
    chomp($values[$_]);
    @vals = $values[$_] =~ /(\S+)/g;

    my $peso = $vals[4];

    if($vals[4] =~ /^([\d\.]+)K$/)
    {
        $peso = $1 * 1000;
    }

    if($peso < $biggestValue)
    {
        $biggestValue = $peso;
        $fileGrosso = $vals[8];
    }

}


print "IL FILE PIù leggero è: $fileGrosso\n";