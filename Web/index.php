<?php
/**
 * Created by PhpStorm.
 * User: Arman Jalalian
 * Date: 5/9/2017
 * Time: 11:03 AM
 */


if(isset($_GET['arrive']))
{
    $arrive = $_GET['arrive'];
    if($arrive == "on")
    {
        $file = fopen("arrive.json", "w") or die ("Can't open file");
        fwrite($file, '{"arrive": "yes"}');
        fclose($file);
    }
    else if($arrive == "off")
    {
        $file = fopen("arrive.json", "w") or die("can't open file");
        fwrite($file, '{"arrive": "no"}');
        fclose($file);
    }
}

?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>OV-Wekker</title>

    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="css/maps.css">
    <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css">
</head>
<body>

<nav class="navbar navbar-inverse">
    <div class="container">
        <div class="navbar-header">
            <a href="#" class="navbar-brand">OV-Wekker</a>
        </div>
</nav>

<div id="map"></div>

<br>

<a id="light_on" href="?arrive=on" class="btn btn-success btn-block btn-lg">Turn On</a>
<br />
<a id="light_off" href="?arrive=off" class="led btn btn-danger btn-block btn-lg">Turn Off</a>
<br />

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
<script src="arrive.js"></script>
<script type="text/javascript" src="js/maps.js"></script>
<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDUTySzB4W56empJ-uhzBbbB_NX7BoEfG8&libraries=places&callback=initMap" async defer></script>

</body>
</html>
