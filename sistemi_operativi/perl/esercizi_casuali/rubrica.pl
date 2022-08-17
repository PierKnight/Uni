#!/usr/bin/perl

print "BENVENUTO NELLA RUBRICA SEMPRE ATTIVA!\n";


%rubrica = ();


$input = <STDIN>;


while(1)
{

    if($input == 0)
    {
        print "Inserire Nome:\n";
        $nome = <STDIN>;
        print "Inserire Numero:\n";
        $numero = <STDIN>;
        $rubrica{$nome} = $numero;
    }
    elsif($input == 1)
    {
        print "Tutti i numeri della rubrica\n";

        for(keys %rubrica)
        {
            print "$_ => $rubrica{$_}\n";
        }
    }
    else
    {
        die("TERMINATA APPLICAZIONE");
    }


    $input = <STDIN>;
}