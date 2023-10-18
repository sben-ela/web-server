#!/usr/bin/php
<?php
$stdin = fopen('php://stdin', 'r');
while ($line = fgets($stdin)) {
    echo $line;
}
fclose($stdin);
?>
