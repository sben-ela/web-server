<?php
$count = 0;

if(isset($_COOKIE['click_count'])) {
    $count = (int)$_COOKIE['click_count'];
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['submit'])) {
    $count++;
    setcookie('click_count', $count);
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