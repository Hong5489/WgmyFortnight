<?php

error_reporting(0);
session_start();

include 'config.php';

if(!isset($_SESSION["id"]) || !isset($_SESSION["username"])) {
    header("Location:login.php");
}

$con = mysqli_connect($db_host, $db_user, $db_pass, $db);
if (!$con) {
    die("Connection error: " . mysqli_connect_error());
}

?>

<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Album | <?=$_SESSION['username']?></title>
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
        <link rel="stylesheet" href="/style.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    </head>
    <body>
        <nav class="navbar navbar-default">
            <div class="container-fluid">
                <div class="navbar-header">
                    <a class="navbar-brand" href="#">Album</a>
                </div>
                <div class="pull-right">
                    <ul class="nav navbar-nav">
                        <li><a href="/logout.php">Logout</a></li>
                    </ul>
                </div>
            </div>
        </nav>
        <div class="album">
            <?php
            if(isset($_POST['url'])) {
                $url = mysqli_real_escape_string($con, $_POST['url']);
                $scheme = parse_url($url, PHP_URL_SCHEME);
                $ext = pathinfo($url, PATHINFO_EXTENSION);
                if (($scheme !== 'http' && $scheme !== 'https') ||
                    ($ext !== 'png' && $ext !== 'jpg')) {
                    echo 'Image format not supported<br>';
                } else {
                    $name = preg_replace('(.png|.jpg)', '', basename($url));
                    $query = "INSERT INTO image (id, user_id, name, url) VALUES (NULL, {$_SESSION['id']}, '\\',0)#', '{$url}')";
                    $result = mysqli_query($con, $query);
                    if($result) {
                        $html = "<div class=\"alert alert-success\" role=\"alert\">";
                        $html .= "Image added successfully</div>";
                    } else {
                        $html = "<div class=\"alert alert-danger\" role=\"alert\">";
                        $html .= "Failed to add image</div>";
                    }
                    echo $html;
                }
            } else if (isset($_POST['delete'])) {
                $id = intval($_POST['delete']);
                $query = "DELETE FROM image WHERE id={$id} AND user_id={$_SESSION['id']}";
                $result = mysqli_query($con, $query);
                if($result) {
                    $html = "<div class=\"alert alert-success\" role=\"alert\">";
                    $html .= "Image deleted successfully</div>";
                } else {
                    $html = "<div class=\"alert alert-danger\" role=\"alert\">";
                    $html .= "Failed to delete image</div>";
                }
                echo $html;
            }
            ?>
            <form class="album-form" action="" method="post">
                <h3>Add new image</h3>
                <div class="input-group">
                    <input type="text" class="form-control" placeholder="URL" name="url" required="required">
                    <span class="input-group-btn">
                        <button type="submit" class="btn btn-primary">Add to album</button>
                    </span>
                </div>
                <div class="text-muted">
                    Only .png and .jpg image format are supported
                </div>
            </form>
            <?php
            $query = "SELECT * FROM image WHERE user_id={$_SESSION['id']}";
            $result = mysqli_query($con, $query);
            if (mysqli_num_rows($result) > 0):
            ?>
                <table class="table table-bordered">
                    <tr>
                        <th>Preview</th>
                        <th>Name</th>
                        <th>Action</th>
                    </tr>
            <?php
                while ($row = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
                    $url = htmlspecialchars($row['url']);
                    $name = htmlspecialchars($row['name']);
                    $html = "<tr>";
                    $html .= "<td><img src='{$url}'></td>";
                    $html .= "<td>{$name}</td>";
                    $html .= "<td><form action='' method='post'>";
                    $html .= "<input type='hidden' name='delete' value='{$row['id']}'>";
                    $html .= "<button type=\"submit\" class=\"btn btn-primary\">Delete</button>";
                    $html .= "</form></td>";
                    $html .= "</tr>";
                    echo $html;
                }
            ?>
                </table>
            <?php
            else:
            ?>
                <div class="alert alert-info" role="alert">There are no image in your album</div>
            <?php
            endif;
            ?>
        </div>
    </body>
</html>

<?php

mysqli_close($con);

?>