#!/usr/bin/perl

#utility per poter ottenere un nuovo file privato dei commenti dichiarati con #
#il comando -r permette di ottenere solo i commenti

die "E' necessario inserire almeno un file!" if @ARGV == 0;

$reverse = 0;

for (@ARGV)
{
    $reverse = 1 if $_ eq "-r";
}

while (@ARGV)
{
    $value = shift @ARGV;
    next unless -e $value;


    open($output,">>",$value . "_out.txt");
    open($file,"<",$value);

    while(<$file>)
    {
        $_ =~ s/#(.+)//g;
        print $output ($reverse ? $1 : $_);
    }

    close($output);
    close($file);

}








