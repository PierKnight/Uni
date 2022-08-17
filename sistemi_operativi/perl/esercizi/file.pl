#!/usr/bin/perl


my $sos = <STDIN>; #questo uso lo stream di import
print STDERR "ERIRIR"; #questo uso per stampare sullo steam di errore!!

#my @array = <STDIN>; #legge tutte le righe successive fino allinserimento id ^D


print @array;

#apertura file:

#open(my <nome stream>, <tipofile>, <nome file>) or die <messaggio in caso di fallimento>
#tipofile : < lettura, > scrittura, +< lettura e scrittura

#per leggere si fa come lo stream input invece di <STDIN> si fa <<nome stream>>
#per la scrittura si usa il print specificando lo stream: print <nome stream> <text>


open(my $file, "<", "input.txt") or die "NON RIESCO AD APRIRE IL FILE\n";
open(my $output, ">", "output.txt") or die "NON RIESCO A SCRIVERE\n";

while(<$file>)
{
    chomp($_);
    print "$_\n";
    print $output $_;
}


print STDERR "SEEE";


close $output;
close $file;