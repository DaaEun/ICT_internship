

<?

header('Content-Type: application/json; charset=utf8');

$servername = "localhost";
$username = "nicecut79";
$password = "Nice2300";
$dbname = "nicecut79";



$conn = new mysqli($servername,$username,$password,$dbname);
if($conn->connect_error) {
    die("Connection Failed: ".$conn->connect_error);
}

//http://emotionreport.co.kr/smart_farm.php

/* select part */

$sql_select = "SELECT id,temperature,humi,light,whumi,date FROM smart_farm ORDER BY id DESC LIMIT 30";
$result =  $conn->query($sql_select);
$sensor_array = array(array('SENSOR','temperature','humidity','light','whumidity'));



if ($result->num_rows > 0){

    while ($row = $result->fetch_assoc()){

        array_push($sensor_array, array(
            $row["date"],(int)$row["temperature"],(int)$row["humi"],(int)$row["light"],(int)$row["whumi"]));

    } //close row


    echo json_encode($sensor_array);

    if(isset($_POST['get_chart'])) {
        exit;
    }
} else {
    echo "0 results";
}

$conn->close();
?>