<?
    $servername = "localhost";
    $username = "nicecut79";
    $password = "Nice2300";
    $dbname = "nicecut79";
    

        $conn = new mysqli($servername,$username,$password,$dbname);
        if($conn->connect_error) {
            die("Connection Failed: ".$conn->connect_error);
        }



    $sql = "SELECT id,temperature,humidity,light,soil,date FROM smart_farm";
    $result =  $conn->query($sql);

    if ($result->num_rows > 0){

        while ($row = $result->fetch_assoc()){

            echo "id" .$row["id"]."----> ";
            echo "Temprature" .$row["temperature"]." - ";
            echo "light:".$row["light"]." - ";
            echo "soil:".$row["soil"]." - ";
            echo  "humi:". $row["humidity"]."<----- ";
            echo "date" .$row["date"]."<br/>";
        }
  } else {
    echo "0 results";
    }


$conn->close();
?>
