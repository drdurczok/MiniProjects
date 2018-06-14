<?php include "header.php"; ?>

<div class="content">

<div class="flex-container">
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriR.png');"></div>
      <img src="img/Stock01a.jpg">
    </a>
  </div>
</div> 

<div class="flex-container">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriL.png');"></div>
      <img src="img/Stock01a.jpg" style="transform: scaleX(-1);">
    </a>
  </div>
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
</div> 

<div class="flex-container">
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriR.png');"></div>
      <img src="img/Stock01a.jpg">
    </a>
  </div>
</div> 

<div class="flex-container">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriL.png');"></div>
      <img src="img/Stock01a.jpg" style="transform: scaleX(-1);">
    </a>
  </div>
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
</div> 

<div class="flex-container">
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriR.png');"></div>
      <img src="img/Stock01a.jpg">
    </a>
  </div>
</div> 

<div class="flex-container">
  <div class="flex-item">
    <a class="img" href="#">
      <div class="overlay" style="background-image: url('img/TriL.png');"></div>
      <img src="img/Stock01a.jpg" style="transform: scaleX(-1);">
    </a>
  </div>
  <div class="flex-item">
    <p>Text</p>
  </div class="flex-item">
</div> 


<br><br><br><br>

<?php
$servername = "localhost";
$username = "s285840";
$password = "";
$dbname = "test";

// Create connection
$con=mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$result = mysqli_query($con,"SELECT * FROM Quotes order by rand() LIMIT 1");

?> <br>

</div>

<?php include "footer.php"; ?>