#!/usr/bin/perl

die "NON CI SONO ARGOMENTI!" if(@ARGV == 0);

open(my $output, ">>", "output.txt");

for $val (@ARGV)
{
    unless(open(my $input, "<", $val))
    {
        print STDERR "SKIPPIN FILE $_\n";
        next;
    }
    else
    {
        print $output "\n-----$val-----\n";
        while (<$input>)
        {
            print $output $_;
        }
        close $input;
    }
}

close $output;