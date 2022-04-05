#!/usr/bin/perl


print "INSERIRE STRINGA:\n";
$stringa = <STDIN>;
chomp($stringa);

print "INSERIRE LETTERA:\n";
$lettera = <STDIN>;
chomp($lettera);

if(length($lettera) > 1)
{
    die "DEVE ESSERE UNA LETTERA!\n";
}

@string_a = split($stringa,"");


print (scalar @string_a) . "\n";

$totale = 0;

for (@string_a)
{
    print "CHAR: $_\n";
    if($_ eq $lettera)
    {
        $totale += 1;
    }
}

print "TOTALE LETTERE: $totale\n";


