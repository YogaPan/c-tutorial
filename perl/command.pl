#!/usr/bin/perl
use strict;
use warnings;

my $command;
my $output;

print('Wich command you want to enter? ');
chomp($command = <STDIN>);

$output = `$command`;
print($output);
