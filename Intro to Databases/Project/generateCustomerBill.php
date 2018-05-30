<html>
<head></head>
<body>


<button style = "height:40px;width:200px" onclick="history.go(-1);">Back </button>
<br> <br>


<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // collect input data
	
	$customerName = $_POST['customerName'];

	$repairId = $_POST['repairId'];


	if(empty($customerName) || empty($repairId)) {
		die(header("location:showBill.html?noInfo=true"));
	}
	 
	if(!empty($customerName)) {
	 	$customerName = prepareInput($customerName);
	}

    if (!empty($repairId)){
		$repairId = prepareInput($repairId);		
    } 

	outputBill($customerName,$repairId);    
}

function prepareInput($inputData){
	$inputData = trim($inputData);
  	$inputData  = htmlspecialchars($inputData);
  	return $inputData;
}


function outputBill($customerName,$repairId){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$employeeNameQuery = oci_parse($conn, "Select name from RepairPerson where employeeNo IN (Select employeeNo from RepairLog Where repairId = :repairId)");
	oci_bind_by_name($employeeNameQuery, ':repairId', $repairId);

	oci_execute($employeeNameQuery);

	if(oci_fetch($employeeNameQuery)) {
		$employeeName = oci_result($employeeNameQuery,'NAME');
	}
	oci_free_statement($employeeNameQuery);

	$query = oci_parse($conn, "Select * From CustomerBill where customerName = :customerName and repairId = :repairId");
	oci_bind_by_name($query, ':repairId', $repairId);
	oci_bind_by_name($query, ':customerName', $customerName);
	
	// Execute the query
	$res = oci_execute($query);


	while(($row = oci_fetch_array($query, OCI_BOTH)) != false) {
		echo "BILL: " . "<br>" . "Machine Id: " . $row['MACHINEID']  . "<br>" . "Customer: ". $row['CUSTOMERNAME'] . "<br>" . "Contact Info: " . $row['CUSTOMERCONTACT'] . "<br>" . "Model: " . $row['MODEL'] . "<br>" . "Repaired by Employee: " . $employeeName . "<br>" . "Brought in on: " . $row['TIMEIN'] . "<br>" . "Finished Repair: " . $row['TIMEOUT'] . "<br>" . "Labor Hours: " . $row['LABORHOURS'] . "<br>" . "Cost of Parts: $" . $row['PARTCOST'] . "<br>" . "Total Cost: $" . $row['TOTALCOST'];
	}

	oci_free_statement($query);
	OCILogoff($conn);
}



?>

</body>
</html>