
<?php 
header('Location: sudoku.php');

$servername = "localhost";
$username = "s285840";
$password = "";
$dbname = "s285840";

// Create connection
$con=mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}


// Get sudoku data from database
$result = mysqli_query($con,"SELECT * FROM SudokuMain");
while ($row = mysqli_fetch_assoc($result)){
    $arr_[0] = str_split($row['TL']);
    $arr_[1] = str_split($row['TM']);
    $arr_[2] = str_split($row['TR']);
    $arr_[3] = str_split($row['ML']);
    $arr_[4] = str_split($row['MM']);
    $arr_[5] = str_split($row['MR']);
    $arr_[6] = str_split($row['BL']);
    $arr_[7] = str_split($row['BM']);
    $arr_[8] = str_split($row['BR']);
}

for ($i = 0; $i <= 8; $i++){
  for ($j = 0; $j <= 8; $j++){
  	if (isset($_POST["input".$i.$j])) {
		$tempval = $_POST["input".$i.$j];
		if (isset($tempval)&&$tempval>0&&$tempval<10) {
			$arr_[$i][$j] = $tempval;
		}
		else if (isset($tempval)&&$tempval==0) {
			$arr_[$i][$j] = 0;
		}
	}
  }
}


// Delete any previous user input from table
$sql = "DELETE FROM SudokuMain";
if ($con->query($sql) === FALSE) {
    echo "Error deleting record: " . $con->error;
}

//echo "var i: " .$var_i."  var j: ".$var_j."  var val: ". $var_val."  arr_ : ".$arr_[$var_i][$var_j]."  implode : ". implode("",$arr_[0]);
for ($i = 0; $i <= 8; $i++){
	$u[$i] = implode("",$arr_[$i]);
}

// Insert new table to database
$sql = "INSERT INTO SudokuMain (TL,TM,TR,ML,MM,MR,BL,BM,BR) VALUES ('$u[0]','$u[1]','$u[2]','$u[3]','$u[4]','$u[5]','$u[6]','$u[7]','$u[8]')";
if ($con->query($sql) === FALSE) {
    echo "Error: " . $sql . "<br>" . $con->error;
}

?>