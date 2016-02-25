#!/usr/bin/perl

print('Wich command you want to enter? ');
chomp($command = <STDIN>);

$output = `$command`;
print($output);
