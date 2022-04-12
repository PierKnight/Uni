#!/usr/bin/perl


qx(rm root.txt);

open($file,"<","/etc/passwd") || die "La cartella passwd non esiste #!"; #apro input stream


while(<$file>) #scorro uno per uno le righe del file
{
    if($_ =~ /root/) #espressione regolare per controllare la presenza di root
    {
        open($output,">>","root.txt") || die "qualcosa è andato storto #!"; #apro output stream, in maniera da appendere il testo
        print $output $_; #stampo le righe che contengono root
        close $output;
    }
}
close $file;