#!/usr/bin/perl

die "NECESSITANO DUE ARGOMENTI" if(scalar @ARGV != 2);


#la mappa contenente gli esiti delle partite, la chiave è la coppia delle squadre che hanno giocato in una partita
%mappa = ();

open($partite,"<",$ARGV[1]) || die "IL FILE \"$ARGV[1]\" non esiste!";
while (<$partite>)
{
    if($_ =~ /(\w+-\w+) +([0-9])-([0-9])/)
    {
        $mappa{$1} = $2 == $3 ? "X" : ($2 > $3 ? "1" : "2"); 
    }
}
close $partite;


open($schedine,"<",$ARGV[0]) || die "IL FILE \"$ARGV[0]\" non esiste!";
open($output,">>","check_prova");


$moltiplicatore = 1;
$not_good = 0;
while(<$schedine>)
{
    if($_ =~ /#Schedina +[0-9]+/)
    {
        print $output $_;
    }
    elsif($_ =~ / *#Importo Scommesso +([1-9][0-9]*)$/)
    {
        chomp $_;
        print $output $_ . "\n";
        print $output "#Moltiplicatore: $moltiplicatore\n";
        print $output "#Possibile Vincita: " . $1 * $moltiplicatore . "\n";
        print $output "#Vincita: " . ($not_good ? "NO" : "SI") . "\n\n";
        $moltiplicatore = 1;
        $not_good = 0;
    }
    elsif($_ =~ /^(\w+-\w+) +(1|2|X) +([0-9]+\.[0-9]*)$/)
    {
        $result = $mappa{$1} eq $2;
        $not_good = 1 if (!$result);

        $moltiplicatore *= $3;

        chomp($_);
        print $output $_ . " ---> " . ($result ? "OK" : "NO") . "\n";
    }
}

close $output;
close $schedine;