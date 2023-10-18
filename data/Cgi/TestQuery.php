<?php
// Get the values of query parameters
$param1 = $_GET['param1'];
$param2 = $_GET['param2'];

if (isset($param1) && isset($param2)) {
    echo "Value of param1: $param1<br>";
    echo "Value of param2: $param2<br>";
} else {
    echo "One or both parameters are missing in the query string.";
}
?>
