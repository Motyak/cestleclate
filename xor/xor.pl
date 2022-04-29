#!/usr/bin/env perl

my $input = join('', <STDIN>);
my $key_file = $ARGV[0];
open my $fh, '<:encoding(UTF-8)', $key_file or die "Can't open file, $!";
read $fh, my $key, -s $fh;

print($input ^ $key);
