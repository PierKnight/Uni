#!/usr/bin/perl

$stringa = "questo è un file che ha % va% simb%li";


#con s prima del regex si può sostituire il risultato trovato
#i char dopo il regex come 'g' applicato certe regole al regex matching

$stringa =~ s/%/sos/g;

#i gruppi trovati dal regex posso essere usati nella sostituzione con lo \<numero gruppo>

print $stringa . "\n";


#con l'attributo g è possibile scorrere tutti i match avvenuti!
#visto che sono diversi match ma con unico gruppo usiamo $1 per accedervi
$frase = "eeeeee erjijek eeeee#7#ee r#?#ele òriew #dre#";
$frase =~ s/#.*?#//g;

while($frase =~ /(\S+)/g) 
{
    print $1 . "\n";
}




