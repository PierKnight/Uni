#!/usr/bin/perl

my $estensioni = shift or die "NECESSARIO DEFINIRE ESTENSIONI\n";


%typeMap = ();

if($estensioni =~ /--format=([\w|\d|,]+)/)
{
    $typeMap{$_} = 0 for(split(/,/, $1));
}
else
{
    die "INVALID FORMAT!\n";
}


my $path = $ARGV[0];
$path = "." unless($path);



@results = qx(du -ka $path);

my $pesoTotale = 0;

for(@results)
{
    for $type (keys %typeMap)
    {
        if($_ =~ /\.$type$/)
        {
            if($_ =~ /^(\d+)/)
            {
                $typeMap{$type} += $1;
                $pesoTotale += $1;
            }
        }
    }
}

for(sort {$typeMap{$a} <=> $typeMap{$b} | $a cmp $b} keys %typeMap)
{
    print "Estensione: $_  " .  $typeMap{$_} . "Kb\n";
}

open($fileOutput, ">", "du.out");
print $fileOutput "Totale occupazione disco della cartella $path: $pesoTotale Kb\n";
close $fileOutput;
