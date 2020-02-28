<?php

error_reporting(0);
session_start();

include 'config.php';

if(isset($_SESSION["id"]) && isset($_SESSION["username"])) {
    header("Location:index.php");
}

?>

<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Album | Login</title>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <link rel="stylesheet" href="/style.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    </head>
    <body>
        <div class="login">
            <?php
            if(isset($_POST['username']) && isset($_POST['password'])) {
                $con = mysqli_connect($db_host, $db_user, $db_pass, $db);
                if (!$con) {
                    die("Connection error: " . mysqli_connect_error());
                }
                $username = mysqli_real_escape_string($con, $_POST['username']);
                $password = hash('sha256', $_POST['password']);
                $query = "SELECT * FROM user WHERE username='{$username}' AND password='{$password}'";
                $result = mysqli_query($con, $query);
                $row  = mysqli_fetch_array($result);
                if(is_array($row)) {
                    $_SESSION["id"] = $row['id'];
                    $_SESSION["username"] = $row['username'];
                    mysqli_close($con);
                    $html = "<script>window.location.href='index.php';</script>";
                } else {
                    mysqli_close($con);
                    $html = "<div class=\"alert alert-danger\" role=\"alert\">";
                    $html .= "Invalid username or password</div>";
                }
                echo $html;
            }
            ?>
            <form class="login-form" action="" method="post">
                <h2 class="text-center">Log in</h2>
                <div class="form-group">
                    <input type="text" class="form-control" placeholder="Username" name="username" required="required">
                </div>
                <div class="form-group">
                    <input type="password" class="form-control" placeholder="Password" name="password" required="required">
                </div>
                <div class="form-group">
                    <button type="submit" class="btn btn-primary btn-block">Log in</button>
                </div>
            </form>
            <p class="text-center">Don't have an account? <a href="/register.php">Register</a></p>
        </div>
    </body>
</html>
