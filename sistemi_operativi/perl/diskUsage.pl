#!/usr/bin/perl

die "TROPPI ARGOMENTI" if @ARGV > 2;

$path = @ARGV != 0 ? $ARGV[-1] : ".";



%extentions = ();

if(@ARGV == 2)
{
    if($ARGV[0] =~ /--format=([\w,]+)/)
    {
        $values = $1;
        while($values =~ /(\w+)/g)
        {
            $extentions{$1} = 1;
        }
    }
    else
    {
        die "INVALID FIRST ARGUMENT!";
    }
}

@files_string = qx(du -ka $path) or die "COMANDO MESSO MALE! #!";
%peso_file = ();
for (@files_string)
{
    if($_ =~ /([0-9]+).*\.(\w+)/ && (@ARGV != 2 || $extentions{$2}))
    {
        $peso_file{$2} += $1;
    }
}

for (sort keys %peso_file)
{
    print STDOUT "Estensione: $_     $peso_file{$_}\n";
}

