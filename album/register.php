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
        <title>Album | Register</title>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <link rel="stylesheet" href="/style.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    </head>
    <body>
        <div class="register">
            <?php
            if(isset($_POST['username']) && isset($_POST['password'])) {
                $con = mysqli_connect($db_host, $db_user, $db_pass, $db);
                if (!$con) {
                    die("Connection error: " . mysqli_connect_error());
                }
                $username = mysqli_real_escape_string($con, $_POST['username']);
                $password = hash('sha256', $_POST['password']);
                $query = "INSERT INTO user (id, username, password) VALUES (NULL, '{$username}', '{$password}')";
                $result = mysqli_query($con, $query);
                if($result) {
                    $html = "<div class=\"alert alert-success\" role=\"alert\">";
                    $html .= "Account created successfully</div>";
                } else {
                    $html = "<div class=\"alert alert-danger\" role=\"alert\">";
                    $html .= "Account creation failed</div>";
                }
                echo $html;
                mysqli_close($con);
            }
            ?>
            <form class="register-form" action="" method="post">
                <h2 class="text-center">Register</h2>
                <div class="form-group">
                    <input type="text" class="form-control" placeholder="Username" name="username" required="required">
                </div>
                <div class="form-group">
                    <input type="password" class="form-control" placeholder="Password" name="password" required="required">
                </div>
                <div class="form-group">
                    <button type="submit" class="btn btn-primary btn-block">Create Account</button>
                </div>
            </form>
            <p class="text-center">Already have an account? <a href="/login.php">Log in</a></p>
        </div>
    </body>
</html>
