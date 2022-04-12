#!/usr/bin/perl

die "E' necessario inserire almeno un file!" if @ARGV == 0;


for (@ARGV)
{
    die "IL FILE $_ NON ESISTE!" unless(-e $_);
}


for $file (@ARGV)
{
    open($daLeggere,"<",$file);
    open($fileOutput,">>","merge.txt");

    while(<$daLeggere>)
    {
        print $fileOutput $_;
    }

    close($fileOutput);
    close($daLeggere);
} 