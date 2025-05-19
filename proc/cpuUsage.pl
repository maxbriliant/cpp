#!/usr/bin/perl -s

use List::Util qw(sum);

$t = $s || 3;

sub c { split ' ', `grep '^cpu ' /proc/stat` }

@a = c(); sleep $t; @b = c();

die "Mangel!\n" if @a < 5 || @b < 5;

$dt = sum(@b[1..@b-1]) - sum(@a[1..@a-1]);
$di = $b[4] - $a[4];

die sprintf "CPU: %.2f%%\n", 100 * ($dt - $di) / $dt if $dt > 0;
die "CPU: 0.00%%\n";