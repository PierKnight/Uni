#!/usr/bin/perl



open($file,"<","/etc/passwd") or "HO NO!";

#file stream reading one by one

$index = 0;

while(<$file>)
{
    print "Line: " . $index . " " . $_ if $index % 2 == 0; #$_ is the default variable when using methods which return something, in this case a line red from a stream
    $index += 1;
}

close $file;