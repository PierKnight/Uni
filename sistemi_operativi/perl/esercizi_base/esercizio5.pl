#!/usr/bin/perl
sub reverseStringa
{
    $len = length($_[0]) - 1;
    $reverse = "";
    for $i (0..$len)
    {
        $reverse = $reverse . substr($_[0],$len - $i, 1);
    }
    return $reverse;
}
print "INSERISCI STRINGA DA INVERTIRE: ";
$input = <STDIN>;
chomp($input);

print reverseStringa($input) . "\n";


