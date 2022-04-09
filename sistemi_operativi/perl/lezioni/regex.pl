#!/usr/bin/perl


$testo = "Oggi è una bella giornata";

if($testo =~ /la/) #la versione/ee/ match se "la" è contenuto nel testo
{
    print "OK!!!!\n" if($testo =~ /la/);
}

if($testo =~ /b.+a/)
{
    print "OK2!!!!\n" if($testo =~ /la/);
}

if("rerwrora rrrerer ora er" =~ /(ora)+/) #matcha quando trova almeno un ora
{
    print "OK3!!!!\n" if($testo =~ /la/);
}

#con =~ otterremo l'esatto contrario, è true se non matcha


#con * il primo match è quello più lungo
#con *? prendi il primo match con il numero minore di di elementi con*

#con l'operatore g ottieni TUTTI i match all'interno della stringa


@matches = ($testo =~ /l.+a/g); #nell'array finiscono tutti i match


#il | crea un or fra tutto quello che c'è a sinistra e tutto quello che c'è a destra di esso. si può rinchiudere con ()

#i match all'interno di parentesi tonde sono inseriti in dei GRUPPI


#-------------CODICE FISCALE-----------------

$codice_fiscale = "MNLTMS73M02L736V";

if($codice_fiscale =~ /^([A-Z]{3})([A-Z]{3})([0-9]{2})([A-Z])([0-9]{2})([A-Z]\d{3})([A-Z])$/)
{
    #qui il codice fiscale è valido
    #con %<numero> si prende il gruppo si possono anche rinonimare

    print "CF Valido\n";
    print "Mese di nascita: $5\n";
}

#si può anche scorrere più di un match per regex con il while(<stringa> =~ <regex>)


$_ = "seeee"; #la variabile $_ viene usata come variabile generica con qualsiasi shortcut 
print;


open (LOG,"tail -f <file> |");

while(<LOG>)
{
    
}