<?
$servername = "localhost";
$username = "nicecut79";
$password = "Nice2300";
$dbname = "nicecut79";

$temp  = $_GET["temp"];
$humi  = $_GET["humi"];
$light  = $_GET["light"];
$whumi = $_GET["whumi"];


$conn = new mysqli($servername,$username,$password,$dbname);
if($conn->connect_error) {
    die("Connection Failed: ".$conn->connect_error);
}
//$sql = "INSERT INTO smart_farm(temperature,humi,light,whumi) VALUES (24,50,56,17)";
//http://emotionreport.co.kr/db_get_insert.php?temp=24&humi=50&light=56&whumi=17

$sql = "INSERT INTO smart_farm(temperature,humi,light,whumi) VALUES ($temp,$humi,$light,$whumi)";

if ($conn->query($sql) === TRUE){
    echo "NEW record Suceessfully";
}else{
    echo "Error" .$sql. "<br/>" . $conn->error;
}

$conn->close();

?>