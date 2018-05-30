<html>
<head></head>
<body>


<button style = "height:40px;width:200px" onclick="history.go(-1);">Back </button>
<br> <br>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // collect input data
	
	//Get Machine Id
	$repairId = $_POST['repairId'];

	//Get the Customer Contract Info
	$contactInfo = $_POST['contactInfo']; 

	if(empty($contactInfo) && empty($repairId)) {
		die(header("location:showStatus.html?noInfo=true"));
	}

    if (!empty($contactInfo)){
		$contactInfo = prepareInput($contactInfo);
		showContactInfoStatus($contactInfo);		
    } 

    if (!empty($repairId)){
		$repairId = prepareInput($repairId);	
		showMachineIdStatus($repairId);	
    } 
	
}

function prepareInput($inputData){
	$inputData = trim($inputData);
  	$inputData  = htmlspecialchars($inputData);
  	return $inputData;
}

function showContactInfoStatus($contactInfo){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$query = oci_parse($conn, "Select status, machineId,repairId From RepairJob where customerContact = :contactInfo");

	oci_bind_by_name($query, ':contactInfo', $contactInfo);
	
	// Execute the query
	$res = oci_execute($query);

	if ($res) {
		$e = oci_error($query); 
        	echo $e['message']; 
	}

	$row = oci_fetch($query);
	if($row != false) {
		while($row != false) {
			echo "Repair Id: " . oci_result($query, 'REPAIRID') . "<br>" . "Machine Id: " . oci_result($query, 'MACHINEID') .  "<br>" . "Status: " . oci_result($query, 'STATUS') ."<br>";
			$row = oci_fetch($query);
		}
	}
	else {
		$query2 = oci_parse($conn, "Select status,machineId,repairId From RepairLog where customerContact =  :customerContact");
		oci_bind_by_name($query2, ':customerContact', $contactInfo);
		oci_execute($query2);

		if(oci_fetch($query2)) {
			echo "Repair Id: " . oci_result($query2, 'REPAIRID') . "<br>" . "Machine Id: " . oci_result($query2, 'MACHINEID') .  "<br>" . "Status: " . oci_result($query2, 'STATUS') ."<br>";
		}
		else {
			echo "Contact Info Has No Jobs Associated With It.";
		}
		oci_free_statement($query2);
	}

	
	oci_free_statement($query);
	OCILogoff($conn);
}

function showMachineIdStatus($repairId){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$query = oci_parse($conn, "Select status, machineId,repairId From RepairJob where repairId = :repairId");

	oci_bind_by_name($query, ':repairId', $repairId);
	
	// Execute the query
	$res = oci_execute($query);

	if (!$res) {
		$e = oci_error($query); 
        	echo $e['message']; 
	}

	$row = oci_fetch($query);
	if($row != false) {
		while($row != false) {
			echo "Repair Id: " . oci_result($query, 'REPAIRID') . "<br>" . "Machine Id: " . oci_result($query, 'MACHINEID') .  "<br>" . "Status: " . oci_result($query, 'STATUS') ."<br>";
			$row = oci_fetch($query);

		}
	}
	else {
		$query2 = oci_parse($conn, "Select status, machineId,repairId From RepairLog where repairId =  :repairId");
		oci_bind_by_name($query2, ':repairId', $repairId);
		oci_execute($query2);

		if(oci_fetch($query2)) {
			echo "Repair Id: " . oci_result($query2, 'REPAIRID') . "<br>" . "Machine Id: " . oci_result($query2, 'MACHINEID') .  "<br>" . "Status: " . oci_result($query2, 'STATUS') ."<br>";
		}
		else {
			echo "Repair Id Has No Jobs Associated With It.";
		}
		oci_free_statement($query2);
	}
	
	

	
	oci_free_statement($query);
	OCILogoff($conn);
}



?>


</body>
</html>