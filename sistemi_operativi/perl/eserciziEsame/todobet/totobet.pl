#!/usr/bin/perl

my $fileScommesse = shift or die "INSERIRE FILE SCOMMESSE";

my $filePartite = shift or die "INSERIRE FILE PARTITE";

qx(rm check.txt);

my %mappaPartite = ();


open($partiteInput, "<", $filePartite);
while(<$partiteInput>)
{
    if($_ =~ /^(\w+-\w+)\s+(\d+)-(\d+)/)
    {
        #se differenza è > 0 vince casa , < 0 vince ospite , se = 0 allora pareggio
        if($2 - $3 > 0)
        {
            $mappaPartite{$1} = "1";
        }
        elsif($2 - $3 < 0)
        {
            $mappaPartite{$1} = "2";
        }
        else
        {
            $mappaPartite{$1} = "X";
        }
    }
}
close $partiteInput;

open(my $scommesseInput, "<", $fileScommesse);
open(my $fileCheck, ">>", "check.txt");

my $moltiplicatore = 1;
my $isValid = 0;

while(<$scommesseInput>)
{


    if($_ =~ /^(\w+-\w+)\s+(\d|X)\s+(\d+\.\w)/)
    {
        my $valid = $mappaPartite{$1} == $2;

        unless($valid)
        {
            $isValid = 0;
        }

        $moltiplicatore = $moltiplicatore * $3;

        chomp($_);
        print $fileCheck $_ . " ---> " . ($valid ? "OK" : "NO") . "\n";
    }
    elsif($_ =~ /#Importo Scommesso\s+(\d+)/)
    {
        print $fileCheck $_;
        print $fileCheck "Moltiplicatore: $moltiplicatore\n";
        print $fileCheck "Possibila vincita: " . ($moltiplicatore * $1) . "\n";
        print $fileCheck "Vincita: " . ($isValid ? "SI" : "NO") . "\n";
        $moltiplicatore = 1;
        $isValid = 1;
    }
    else
    {
        print $fileCheck $_;
    }

    
    

}

close $fileCheck;
close $scommesseInput;