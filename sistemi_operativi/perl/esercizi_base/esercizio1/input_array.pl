#!/usr/bin/perl




@numeri = ();


$input = <STDIN>;
chomp($input);

while($input != -1)
{
    push(@numeri,$input);
    print "INSERITO: $input \n";
    $input = <STDIN>;
    chomp($input);  
}

$sommaTotale = 0;

$sommaTotale += $_ for (@numeri);


print "SOMMA TOTALE: $sommaTotale\n"; 

