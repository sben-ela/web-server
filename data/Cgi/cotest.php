<?php
// Initialize the count variable
$count = 0;

// Check if the cookie exists
if(isset($_COOKIE['click_count'])) {
    $count = (int)$_COOKIE['click_count'];
}

// Check if the form has been submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['submit'])) {
    // Increment the count
    $count++;
    // echo $count;
    // echo "<br>";
    // Set the cookie to store the updated count
    setcookie('click_count', $count, time() + 3600); // Cookie expires in 1 hour
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Click Counter with Cookie</title>
</head>
<body>
    <h1>Click Counter with Cookie</h1>
    <p>Number of clicks: <?php echo $count; ?></p>
    <form method="post">
        <input type="submit" name="submit" value="Submit">
    </form>
</body>
</html>