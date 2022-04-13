#!/usr/bin/env perl

my $input = join("", <STDIN>);
my $key = $ARGV[0];

print($input ^ $key);
