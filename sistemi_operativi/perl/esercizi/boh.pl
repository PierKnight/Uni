#!/usr/bin/perl
my %map = (ciao => sos);


my $input = <STDIN>;

chomp($input);

$map{"WOWOW"} = "SSSSSS";
die "SAD NON E PRESENTE IL VALORE" unless($map{$input});

print $map{$input};
