#!/usr/bin/env perl

package utils;

sub parseArgs {
    my ($userInput, $sep) = @_;
    $sep //= ';';

    return split($sep, $userInput);
}

package today;
use POSIX 'strftime';

sub yday { return strftime('%-j', localtime); }
sub year { return strftime('%Y' , localtime); }

package main;
use POSIX 'floor';

sub yearProgress {
    my ($yday, $year) = @_;
    $yday //= today::yday();
    $year //= today::year();

    my $isLeapYear = $year % 4 == 0;
    my $nbOfDaysInYear = 365 + $isLeapYear;
    my $percentage = floor($yday / $nbOfDaysInYear * 100);
    return $percentage . '%';
}

sub yearProgressFromStr {
    my ($str) = @_;

    my @args = utils::parseArgs($str);
    $str eq '' ? yearProgress() : yearProgress(@args)
}

my $input = join('', <STDIN>);
my $res = yearProgressFromStr($input);
print($res);
