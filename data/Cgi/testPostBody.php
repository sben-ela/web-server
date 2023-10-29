#!/usr/bin/php
<?php

// Open standard input (stdin)
$stdin = fopen('php://stdin', 'r');

if ($stdin === false) {
    // Handle the case where opening stdin fails
    die("Failed to open stdin.\n");
}

while ($line = fgets($stdin)) {
    // Process and echo each line from stdin
    echo $line;
}

// Close stdin when done (optional)
fclose($stdin);
