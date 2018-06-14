<?php include "header.php"; ?>

<body>

<?php
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
    $arr[0] = str_split($row['TL']);
    $arr[1] = str_split($row['TM']);
    $arr[2] = str_split($row['TR']);
    $arr[3] = str_split($row['ML']);
    $arr[4] = str_split($row['MM']);
    $arr[5] = str_split($row['MR']);
    $arr[6] = str_split($row['BL']);
    $arr[7] = str_split($row['BM']);
    $arr[8] = str_split($row['BR']);  
}

$result = mysqli_query($con,"SELECT * FROM SudokuTemp");
while ($rowT = mysqli_fetch_assoc($result)){
    $arrT[0] = str_split($rowT['TL']);
    $arrT[1] = str_split($rowT['TM']);
    $arrT[2] = str_split($rowT['TR']);
    $arrT[3] = str_split($rowT['ML']);
    $arrT[4] = str_split($rowT['MM']);
    $arrT[5] = str_split($rowT['MR']);
    $arrT[6] = str_split($rowT['BL']);
    $arrT[7] = str_split($rowT['BM']);
    $arrT[8] = str_split($rowT['BR']);  
}

for ($i = 0; $i <= 8; $i++){
  for ($j = 0; $j <= 8; $j++){
    if ($arr[$i][$j] != 0 && $arrT[$i][$j] != 0){
      $arr[$i][$j] = "value=\"".$arr[$i][$j]."\" disabled";
    }
    else if ($arr[$i][$j] != 0 && $arrT[$i][$j] == 0){
      $arr[$i][$j] = "value=\"".$arr[$i][$j]."\"name=\"input".$i.$j."\" style=\"color:blue\"";
    }
    else{
      $arr[$i][$j] = "name=\"input".$i.$j."\"";
    }
  }
}

//Work on user input: replace zeros with user input and save to database

 //$type = mysql_real_escape_string($row['TL']);

 /* Working
 $i_arr[0] = json_encode($i_arr[0]);
 $i_arr[1] = json_encode($i_arr[1]);
 $i_arr[2] = json_encode($i_arr[2]);
 $i_arr[3] = json_encode($i_arr[3]);
 $i_arr[4] = json_encode($i_arr[4]);
 $i_arr[5] = json_encode($i_arr[5]);
 $i_arr[6] = json_encode($i_arr[6]);
 $i_arr[7] = json_encode($i_arr[7]);
 $i_arr[8] = json_encode($i_arr[8]);
 $sql = "INSERT INTO SudokuMain (TL,TM,TR,ML,MM,MR,BL,BM,BR) VALUES ('$arr[0]','$arr[1]','$arr[2]','$arr[3]','$arr[4]','$arr[5]','$arr[6]','$arr[7]','$arr[8]')";
 if ($con->query($sql) === FALSE) {
    echo "Error: " . $sql . "<br>" . $con->error;
}
*/

?>

<div class="container">
  
  <h1>Sudoku Board</h1>
  <form action="action.php" method="post">
    <table id="grid">

      <tr>
        <td><input id="cell-0"  type="text" <?= $arr[0][0] ?> ></td>
        <td><input id="cell-1"  type="text" <?= $arr[0][1] ?> ></td>
        <td><input id="cell-2"  type="text" <?= $arr[0][2] ?> ></td>
        
        <td><input id="cell-3"  type="text" <?= $arr[1][0] ?> ></td>
        <td><input id="cell-4"  type="text" <?= $arr[1][1] ?> ></td>
        <td><input id="cell-5"  type="text" <?= $arr[1][2] ?> ></td>
        
        <td><input id="cell-6"  type="text" <?= $arr[2][0] ?> ></td>
        <td><input id="cell-7"  type="text" <?= $arr[2][1] ?> ></td>
        <td><input id="cell-8"  type="text" <?= $arr[2][2] ?> ></td>
      </tr>

      <tr>
        <td><input id="cell-9"  type="text" <?= $arr[0][3] ?> ></td>
        <td><input id="cell-10" type="text" <?= $arr[0][4] ?> ></td>
        <td><input id="cell-11" type="text" <?= $arr[0][5] ?> ></td>
        
        <td><input id="cell-12" type="text" <?= $arr[1][3] ?> ></td>
        <td><input id="cell-13" type="text" <?= $arr[1][4] ?> ></td>
        <td><input id="cell-14" type="text" <?= $arr[1][5] ?> ></td>
      
        <td><input id="cell-15" type="text" <?= $arr[2][3] ?> ></td>
        <td><input id="cell-16" type="text" <?= $arr[2][4] ?> ></td>
        <td><input id="cell-17" type="text" <?= $arr[2][5] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-18" type="text" <?= $arr[0][6] ?> ></td>
        <td><input id="cell-19" type="text" <?= $arr[0][7] ?> ></td>
        <td><input id="cell-20" type="text" <?= $arr[0][8] ?> ></td>
        
        <td><input id="cell-21" type="text" <?= $arr[1][6] ?> ></td>
        <td><input id="cell-22" type="text" <?= $arr[1][7] ?> ></td>
        <td><input id="cell-23" type="text" <?= $arr[1][8] ?> ></td>
        
        <td><input id="cell-24" type="text" <?= $arr[2][6] ?> ></td>
        <td><input id="cell-25" type="text" <?= $arr[2][7] ?> ></td>
        <td><input id="cell-26" type="text" <?= $arr[2][8] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-27" type="text" <?= $arr[3][0] ?> ></td>
        <td><input id="cell-28" type="text" <?= $arr[3][1] ?> ></td>
        <td><input id="cell-29" type="text" <?= $arr[3][2] ?> ></td>
        
        <td><input id="cell-30" type="text" <?= $arr[4][0] ?> ></td>
        <td><input id="cell-31" type="text" <?= $arr[4][1] ?> ></td>
        <td><input id="cell-32" type="text" <?= $arr[4][2] ?> ></td>
        
        <td><input id="cell-33" type="text" <?= $arr[5][0] ?> ></td>
        <td><input id="cell-34" type="text" <?= $arr[5][1] ?> ></td>
        <td><input id="cell-35" type="text" <?= $arr[5][2] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-36" type="text" <?= $arr[3][3] ?> ></td>
        <td><input id="cell-37" type="text" <?= $arr[3][4] ?> ></td>
        <td><input id="cell-38" type="text" <?= $arr[3][5] ?> ></td>
        
        <td><input id="cell-39" type="text" <?= $arr[4][3] ?> ></td>
        <td><input id="cell-40" type="text" <?= $arr[4][4] ?> ></td>
        <td><input id="cell-41" type="text" <?= $arr[4][5] ?> ></td>
        
        <td><input id="cell-42" type="text" <?= $arr[5][3] ?> ></td>
        <td><input id="cell-43" type="text" <?= $arr[5][4] ?> ></td>
        <td><input id="cell-44" type="text" <?= $arr[5][5] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-45" type="text" <?= $arr[3][6] ?> ></td>
        <td><input id="cell-46" type="text" <?= $arr[3][7] ?> ></td>
        <td><input id="cell-47" type="text" <?= $arr[3][8] ?> ></td>
        
        <td><input id="cell-48" type="text" <?= $arr[4][6] ?> ></td>
        <td><input id="cell-49" type="text" <?= $arr[4][7] ?> ></td>
        <td><input id="cell-50" type="text" <?= $arr[4][8] ?> ></td>
        
        <td><input id="cell-51" type="text" <?= $arr[5][6] ?> ></td>
        <td><input id="cell-52" type="text" <?= $arr[5][7] ?> ></td>
        <td><input id="cell-53" type="text" <?= $arr[5][8] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-54" type="text" <?= $arr[6][0] ?> ></td>
        <td><input id="cell-55" type="text" <?= $arr[6][1] ?> ></td>
        <td><input id="cell-56" type="text" <?= $arr[6][2] ?> ></td>
        
        <td><input id="cell-57" type="text" <?= $arr[7][0] ?> ></td>
        <td><input id="cell-58" type="text" <?= $arr[7][1] ?> ></td>
        <td><input id="cell-59" type="text" <?= $arr[7][2] ?> ></td>
        
        <td><input id="cell-60" type="text" <?= $arr[8][0] ?> ></td>
        <td><input id="cell-61" type="text" <?= $arr[8][1] ?> ></td>
        <td><input id="cell-62" type="text" <?= $arr[8][2] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-63" type="text" <?= $arr[6][3] ?> ></td>
        <td><input id="cell-64" type="text" <?= $arr[6][4] ?> ></td>
        <td><input id="cell-65" type="text" <?= $arr[6][5] ?> ></td>
      
        <td><input id="cell-66" type="text" <?= $arr[7][3] ?> ></td>
        <td><input id="cell-67" type="text" <?= $arr[7][4] ?> ></td>
        <td><input id="cell-68" type="text" <?= $arr[7][5] ?> ></td>
        
        <td><input id="cell-69" type="text" <?= $arr[8][3] ?> ></td>
        <td><input id="cell-70" type="text" <?= $arr[8][4] ?> ></td>
        <td><input id="cell-71" type="text" <?= $arr[8][5] ?> ></td>
      </tr>

      <tr>          
        <td><input id="cell-72" type="text" <?= $arr[6][6] ?> ></td>
        <td><input id="cell-73" type="text" <?= $arr[6][7] ?> ></td>
        <td><input id="cell-74" type="text" <?= $arr[6][8] ?> ></td>
      
        <td><input id="cell-75" type="text" <?= $arr[7][6] ?> ></td>
        <td><input id="cell-76" type="text" <?= $arr[7][7] ?> ></td>
        <td><input id="cell-77" type="text" <?= $arr[7][8] ?> ></td>
        
        <td><input id="cell-78" type="text" <?= $arr[8][6] ?> ></td>
        <td><input id="cell-79" type="text" <?= $arr[8][7] ?> ></td>
        <td><input id="cell-80" type="text" <?= $arr[8][8] ?> ></td>
      </tr>

    </table>
    <input type="submit">
  </form>
</div>

</body>

<?php include "footer.php"; ?>