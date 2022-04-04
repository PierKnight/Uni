#!/usr/bin/perl

#esecuzione file perl test.pl per fare direttamente, oppure sfruttare la shebang con ./test.pl

#use strict;
#use warnings;

my $variabile = 3;

print "Hello world $variabile\n";


#tipologgia di variabili

#SCALARI ----> sono le variabili che ci permette di salvare un singolo dato TIPO BASE
#ARRAY ----> contenitori di tipi base
#MAPPE ---> associano una chiave ad un valore

# dichiarazione variabili scalari con il $ avanti

my $nome_variabile; #questa variabile di default è undef


#le stringhe si concatenano con il .
$eee = "eeee" . 2 . "eeee";

#in pearl non esiste un concetto di true/false ma si usa 1 o 0
#qualsiasi valore >= 1 nel contesto di check ritorna true

#I VALORI SCALARI POSSONO ANCHE ESSERE FILE HANDLER

#con questo apriamo il file
open($file_handler, ">>" , "testo.txt") || die "$! Oh no, non è andato bene"; #il comando die termina l'esecuzione specificando anche il motivo, $! è la info fornito da perl

#il print scriverà sul file
print $file_handler "ciao\n" ;

#chiudiamo il file handler
close $file_handler;

#DICHIARAZIONE E USO DI ARRAY
#sono preceduti dal simbolo @
@array;
@array = (1,2,3);

#modificare elemento, usiamo il dollaro perchè è uno scalare, alla fine i simboli indicano come lo dobbiamo trattare
$array[2] = 4;

#con $#array prendiamo l'ultimo indice dell'array
$last_index  = $#array;
#size dell'array
$size = scalar @array;

print "@array\n";

#si possono anche usare indici negative per partire dalla fine
print "LAST ELEMENT:  $array[-1]\n";


#creo un nuovo array come sottinsieme di un'altro
@new_array = @array[1..2];

@sorted_array = sort @array;#crea una copia ordinata dell'array dato in input

#per aggiungere e rimuovere elementi ci sono le instruzioni push / pop alla fine dell array

push @new_array, 5;
$sos = pop @new_array; #ritorna anche l'elemento rimosso
print "$sos\n";

#la controparte UGUALE ma applicata all'inizio dell'array è unshift/shift
#NOTA BENISSIMO
#il sort ordina a seconda del contesto!!! se io ho un array con "1","2","11" diventa ----> "1", "11","2"


#puoi avere array con tipi diversi, se è presente una stringa tutto diventa una stringa ma se io prendo un elemento che è int lo prendo correttamente


#PASSARE ARGOMENTI DALLA LINEA DI COMANDO
#gli arg sono inseriti dentro un array accessibile con @ARGV

#cerco di prendere il primo elemento dell'array, se non è possibile esegui altro comando, che in questo caso termina il programma
$valore = shift @ARGV || die "è necessario almeno un arg\n";

if (scalar @ARGV != 0)
{
    print "ARGOMENTI PASSATI: @ARGV\n";
}


#LE MAPPE (LE HASH INSOMMA)
#sono preceduti dal simbolo %

#si possono dichiarare con degli elementi dentro oppure inserirli dopo
%hash;

#INIZIALIZZAZIONE
#%hash ("Francesco",1,"SOOOS",2);
#oppure
%hash = (
    "francesco" => 1,
    "SOOOS" => 2
);
#non puoi pretendere che i table siano ordinati, la stampa non avrà sempre lo stesso ordine
#bisogna ordinare il table con la sort

#accesso ad un valore 
if(not $hash{"francesco"})
{
    print "OH NO NON HAI LA KEY\n;"
}
else
{
    print "YAY\n";
}
#questo fa la stessa cosa di quello di prima!
print !$hash{"francesco"} ? "OH NO NON HAI LA KEY\n;" : "YAY\n";


#con sub puoi creare e chiamare blocchi di codice
sub metodo()
{
    print "METODO\n";
}
metodo();

#"unless" è il negato dell'if, se lo statement è false allora chiama il metodo
#else if si scrive con "elsif"


#for e foreach sono la stessa cosa in perl

#while(@array) itera finchè l'array non è vuoto
#until è il not del while



#scorrere le mappe

%mappa = (test => 1, sos => 2);
#metodo 1

@chiavi = keys %mappa; #ottengo un array di chiavi della mappa
@values = values %mappa; #ottengo un array di valori della mappa


while (($chiave,$valore) = each %mappa) #scorro tutte le entry della mappa
{

}

