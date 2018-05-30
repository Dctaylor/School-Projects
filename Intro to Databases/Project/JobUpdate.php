<html>
<head></head>
<body>


<button style = "height:40px;width:200px" onclick="history.go(-1);">Back </button>
<br> <br>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // collect input data
	
	$repairId = $_POST['repairId'];

	$newStatus = $_POST['newStatus'];

    $currentTime = $_POST['currentTime'];
	 
    $partCosts = $_POST['pCosts']; 
	 
	$laborHours = $_POST['lHours'];

	$problemCode1 = $_POST['problemCode1'];

	$problemCode2 = $_POST['problemCode2'];

	$problemCode3 = $_POST['problemCode3'];

	$problemCode4 = $_POST['problemCode4'];


	if(empty($repairId) || empty($newStatus)) {
		die(header("location:updateRepair.html?noInfo=true"));
	}

	if(strcasecmp($newStatus, 'Under_Repair') != 0 && strcasecmp($newStatus, 'Ready') != 0 && strcasecmp($newStatus, 'Done') != 0 && strcasecmp($newStatus, 'Unchanged') != 0) {
		die(header("location:updateRepair.html?wrongStatus=true"));
	}
	 
	if(!empty($repairId)) {
	 	$repairId = prepareInput($repairId);
	}

    if (!empty($newStatus)){
		$newStatus = prepareInput($newStatus);		
    } 

	if (!empty($partCosts)){
		$partCosts = prepareInput($partCosts);		
    }
    if (!empty($laborHours)){
		$laborHours = prepareInput($laborHours);		
    } 
    if (!empty($currentTime)){
		$currentTime = prepareInput($currentTime);		
    } 


	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}


	$checkRepair = oci_parse($conn, "Select * from RepairJob where repairId = :repairId");
	oci_bind_by_name($checkRepair, ':repairId', $repairId);
	oci_execute($checkRepair);
	if(!oci_fetch($checkRepair)) {
		echo 'Invalid Repair Id';
	}
	else {
		if(!empty($problemCode1)) {
	 		$problemCode1 = prepareInput($problemCode1);
	 		updateProblemReport($repairId,$problemCode1);
		}

		if(!empty($problemCode2)) {
	 		$problemCode2 = prepareInput($problemCode2);
	 		updateProblemReport($repairId,$problemCode2);
		}

		if(!empty($problemCode3)) {
	 		$problemCode3 = prepareInput($problemCode3);
	 		updateProblemReport($repairId,$problemCode3);
		}

		if(!empty($problemCode4)) {
	 		$problemCode4 = prepareInput($problemCode4);
	 		updateProblemReport($repairId,$problemCode4);
		}

		if(strcasecmp($newStatus, 'Done') == 0) {
    		if(empty($partCosts) || empty($laborHours)) {
				die(header("location:updateRepair.html?noInfo=true"));
			}
			updateJob($repairId,$newStatus);
			updateLog($repairId,$currentTime,$partCosts,$laborHours,$currentTime);
    	}
    	else {
			updateJob($repairId,$newStatus);    	
    	}	
	}
	oci_free_statement($checkRepair);

    
}

function prepareInput($inputData){
	$inputData = trim($inputData);
  	$inputData  = htmlspecialchars($inputData);
  	return $inputData;
}

function updateProblemReport($repairId,$problemCode){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}


	$query = oci_parse($conn, "Insert Into ProblemReport(repairId,problemId) values(:repairId,:problemCode)");
	
	oci_bind_by_name($query, ':repairId', $repairId);
	oci_bind_by_name($query, ':problemCode', $problemCode);
	
	// Execute the query
	$res = oci_execute($query);

	if (!$res) {
		$e = oci_error($query); 
        	echo $e['Error']; 
	}
	else {
		echo 'Problems Added to Report <br>';
	}

	oci_free_statement($query);
	OCILogoff($conn);
}

function updateJob($repairId,$newStatus){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	if(strcasecmp($newStatus, 'Unchanged') != 0) {
		$query = oci_parse($conn, "Update RepairJob set status = :newStatus where repairId = :repairId");
		oci_bind_by_name($query, ':newStatus', $newStatus);
		oci_bind_by_name($query, ':repairId', $repairId);
	
	
		// Execute the query
		$res = oci_execute($query);

		if (!$res) {
			$e = oci_error($query); 
        	echo $e['Error']; 
		}
		else {
			echo "Update Successful";
		}

		oci_free_statement($query);
	}
	else {
		echo "Job Status Unchanged <br>";
	}	

	OCILogoff($conn);
}

function updateLog($repairId,$currentTime,$partCosts,$laborHours,$currentTime){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$jobQuery = oci_parse($conn,"Select * from RepairJob where repairId = :repairId");
	oci_bind_by_name($jobQuery, ':repairId', $repairId);
	oci_execute($jobQuery);
	$row = oci_fetch($jobQuery);
	while($row != false) {
		$itemId = oci_result($jobQuery, 'MACHINEID');
		$contractId = oci_result($jobQuery, 'CONTRACTID');
		$customerName = oci_result($jobQuery, 'CUSTOMERNAME');
		$contactInfo = oci_result($jobQuery, 'CUSTOMERCONTACT');
		$timeOfArrival = oci_result($jobQuery, 'TIMEOFARRIVAL');
		$status = oci_result($jobQuery, 'STATUS');
		$employeeNo = oci_result($jobQuery, 'EMPLOYEENO');
		$row = oci_fetch($jobQuery);
	}

	$query = oci_parse($conn, "Insert Into RepairLog(repairId,machineId,contractId,customerName,customerContact,timeOfArrival,status,employeeNo) values(:repairId,:itemId,:contractId,:customerName,:contactInfo,:timeOfArrival,:status,:employeeNo)");
	
	oci_bind_by_name($query, ':repairId', $repairId);
	oci_bind_by_name($query, ':itemId', $itemId);
	oci_bind_by_name($query, ':contractId', $contractId);
	oci_bind_by_name($query, ':customerName', $customerName);
	oci_bind_by_name($query, ':contactInfo', $contactInfo);
	oci_bind_by_name($query, ':timeOfArrival', $timeOfArrival);
	oci_bind_by_name($query, ':status', $status);
	oci_bind_by_name($query, ':employeeNo', $employeeNo);
	

	// Execute the query
	$res = oci_execute($query);

	if (!$res) {
		$e = oci_error($query); 
        	echo $e['Error']; 
	}


	$deleteJob= oci_parse($conn, "Delete from RepairJob where repairId = :repairId");
	oci_bind_by_name($deleteJob, ':repairId', $repairId);
	$res = oci_execute($deleteJob);
	oci_free_statement($deleteJob);

	if (!$res) {
		$e = oci_error($query); 
        	echo $e['Error']; 
	}

	$itemQuery = oci_parse($conn, "Select model,price from RepairItems where itemId = :itemId");
	oci_bind_by_name($itemQuery, ':itemId', $itemId);
	oci_execute($itemQuery);
	if(oci_fetch($itemQuery)) {
		$model = oci_result($itemQuery,'MODEL');
		$price = oci_result($itemQuery,'PRICE');
	}

	oci_free_statement($itemQuery);

	$deleteItem= oci_parse($conn, "Delete from RepairItems where itemId = :itemId");
	oci_bind_by_name($deleteItem, ':itemId', $itemId);
	$res = oci_execute($deleteItem);
	oci_free_statement($deleteItem);


	if (!$res) {
		$e = oci_error($query); 
        	echo $e['Error']; 
	}
	
	oci_free_statement($jobQuery);
	oci_free_statement($query);
	OCILogoff($conn);

	createNewBill($repairId,$currentTime,$partCosts,$laborHours,$model,$price,$currentTime);
}

function createNewBill($repairId,$currentTime,$partCosts,$laborHours,$model,$price,$currentTime){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$jobQuery = oci_parse($conn,"Select * from RepairLog where repairId = :repairId");
	oci_bind_by_name($jobQuery, ':repairId', $repairId);
	oci_execute($jobQuery);
	while(($row = oci_fetch_array($jobQuery, OCI_BOTH)) != false) {
		$itemId = $row['MACHINEID'];
		$customerName = $row['CUSTOMERNAME'];
		$contactInfo = $row['CUSTOMERCONTACT'];
		$timeOfArrival = $row['TIMEOFARRIVAL'];
		$employeeNo = $row['EMPLOYEENO'];
	}

	oci_free_statement($jobQuery);

	
	if($price == 0) {
		$totalCost = 0.00;
	}
	else{
		$totalCost = $price + $partCosts;
	}

	$query = oci_parse($conn, "Insert Into CustomerBill(repairId,machineId,customerName,customerContact,model,employeeNo,timeIn,timeOut,laborHours,partCost,totalCost) values(:repairId,:itemId,:customerName,:contactInfo,:model,:employeeNo,:timeOfArrival,:currentTime,:laborHours,:partCosts,:totalCost)");
	
	oci_bind_by_name($query, ':repairId', $repairId);
	oci_bind_by_name($query, ':itemId', $itemId);
	oci_bind_by_name($query, ':customerName', $customerName);
	oci_bind_by_name($query, ':contactInfo', $contactInfo);
	oci_bind_by_name($query, ':model', $model);
	oci_bind_by_name($query, ':employeeNo', $employeeNo);
	oci_bind_by_name($query, ':timeOfArrival', $timeOfArrival);
	oci_bind_by_name($query, ':currentTime', $currentTime);
	oci_bind_by_name($query, ':laborHours', $laborHours);
	oci_bind_by_name($query, ':partCosts', $partCosts);
	oci_bind_by_name($query, ':totalCost', $totalCost);
	
	
	// Execute the query
	$res = oci_execute($query);

	if(!$res) {
		$e = oci_error($query); 
        	echo $e['Error']; 
	}
	
	
	oci_free_statement($query);
	OCILogoff($conn);
}



?>

</body>
</html>