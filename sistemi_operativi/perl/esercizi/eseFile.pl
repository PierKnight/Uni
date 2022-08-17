#!/usr/bin/perl

open($file, "<", "/etc/passwd") or die "NON SONO RIUSCITO A LEGGERE IL FILE";
open($output, ">>", "output.txt") or die "NON SONO RIUSCITO A SCRIVERE SUL FILE";

my $index = 0;

#stampa delle sole righe pari
while(<$file>)
{


    if($_ =~ "bash")
    {
        print $output $_;
    }

    if($index % 2 == 0)
    {
        chomp($_);
        print "$_\n";
    }

    $index++;
}

close $output;
close $file;