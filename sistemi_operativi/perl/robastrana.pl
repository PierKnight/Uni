#!/usr/bin/perl



@array = qx(ps);

for(1..@array)
{
    $stringa = $array[$_];


    if($stringa =~ /\s*(\S+)\s+(\S+)\s+(\S+)\s+(.+)/)
    {
        print $4 . "\n";
    }


}

