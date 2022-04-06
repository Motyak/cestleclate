#!/usr/bin/env perl

use POSIX qw(strftime floor);

package utils;
sub parseArgs
{
    my ($userInput, $sep) = @_;
    $sep //= ';';

    return split($sep, $userInput);
}

package today;
sub yday { return main::strftime('%-j', localtime); }
sub year { return main::strftime('%Y' , localtime); }

package main;

sub yearProgress
{
    my ($yday, $year) = @_;
    $yday //= today::yday();
    $year //= today::year();

    my $isLeapYear = $year % 4 == 0;
    my $nbOfDaysInYear = 365 + 1 * $isLeapYear;
    my $percentage = floor($yday / $nbOfDaysInYear * 100);
    return $percentage . '%';
}

sub yearProgressFromStr
{
    my ($str) = @_;

    if($str eq '')
    {
        return yearProgress();
    }
    my @args = utils::parseArgs($str);

    return yearProgress(@args);
}

my @input;
while (<STDIN>)
{
    push @input, $_;
}
my $userInput = join('', @input);
my $res = yearProgressFromStr($userInput);
print($res);
