#!/usr/bin/perl
#die "SONO NECESSARI DUE ARGOMENTI!" if(@ARGV != 2);
#my $length = shift; #shift senza argomento mi permette di prendere e rimuovere il primo elemento degli argomenti
#my $name = shift;
#for (0..$length)
#{
#    my $fileName = $name . $_ . "\.txt";
#    qx(touch $fileName);
#}

@aaa = open(my $fh, "<", "ses.txt") or die "Can’t open < input.txt: $!";
$element = <$fh>;
print $element . "aaaa\n";
close $fh;



while(<STDIN>)
{

    chomp;
    last if($_ eq "ses");
    print $_ . "\n";
}
