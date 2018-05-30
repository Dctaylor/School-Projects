<html>
<head></head>
<body>

<button style = "height:40px;width:200px" onclick="history.go(-1);">Back </button>
<br> <br>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // collect input data
	
	//Get Customer Name
	$customerName = $_POST['customerName'];

	//Get the Customer Contract Info
	$contactInfo = $_POST['contactInfo'];

	// Get the contractId
    $contractId = $_POST['contractId']; 
	 
	// Get the machine type
    $type = $_POST['type']; 
	 
	// Get the machine model
	$model = $_POST['model'];

	//Get the year of machine 
	$year = $_POST['year'];

	if(empty($customerName) || empty($contactInfo) || empty($type) || empty($model) || empty($year)) {
		die(header("location:newMachine.html?noInfo=true"));
	}
	

	if(!empty($customerName)) {
	 	$customerName = prepareInput($customerName);
	}
    if (!empty($contactInfo)){
		$contactInfo = prepareInput($contactInfo);		
    } 

    if (!empty($contractId)){
		$contract = prepareInput($contractId);		
    } 
    else {
     	$contractId = 'None';
    }

    if (!empty($model)){
		$model = prepareInput($model);		
    } 
    if (!empty($year)){
		$year = prepareInput($year);		
    }

    if(strcasecmp($type, 'Computer') != 0 && strcasecmp($type, 'Printer') != 0) {
		die(header("location:newMachine.html?badInfo=true"));
	} 

    $conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	    print "<br> connection failed:";       
        exit;
	}

    if(strcasecmp($contractId, 'None') != 0) {
		$serviceContractQuery = oci_parse($conn, "Select * from ServiceContract where contractId = :contract");

		oci_bind_by_name($serviceContractQuery, ':contract', $contractId);
		oci_execute($serviceContractQuery);
		if(!oci_fetch($serviceContractQuery)) {
			echo 'Invalid Contract Id.  Creating job for regular price.'; 
			$contractId = 'None';
			$contractType = 'None';
			$contractType = prepareInput($contractType);
			$price = randomFloat(100,500);
			$price = round($price,2);
		}
		else {
			$nameQuery = oci_parse($conn, "Select * from ServiceContract where contractId = :contract");
			oci_bind_by_name($nameQuery, ':contract', $contractId);
			oci_execute($nameQuery);
			$row = oci_fetch($nameQuery);
			if($row != false) {
				$endDateString = oci_result($nameQuery, 'ENDDATE');
				$nameCheck = oci_result($nameQuery, 'CUSTOMERNAME');
			}
			oci_free_statement($nameQuery);

			$endDate = new DateTime($endDateString);
			$today = date("Y-m-d");
			$todayDate = new DateTime($today);
			if(strcasecmp($nameCheck, $customerName) != 0) {
				echo 'Name does not match Service Contact.  Creating job for regular price'; 
				$contractId = 'None';
				$contractType = 'None';
				$price = randomFloat(100,500);
				$price = round($price,2);
			}
			else if($endDate < $todayDate) {
				echo 'Contract has expired. Creating job for regular price'; 
				$contractId = 'None';
				$contractType = 'None';
				$price = randomFloat(100,500);
				$price = round($price,2);
			}
			else {
				$price = 0;
				$contractTypeQuery = oci_parse($conn, "Select contractType from ServiceContract where contractId = :contract");
				oci_bind_by_name($contractTypeQuery, ':contract', $contractId);
				oci_execute($contractTypeQuery);
				if(oci_fetch($contractTypeQuery) != false) {
					$serviceContractType = oci_result($contractTypeQuery,'CONTRACTTYPE');
					if(strcasecmp($serviceContractType, 'Single') == 0) {
						$contractType = 'Single';
						$contractType = prepareInput($contractType);
					}
					else {
						$contractType = 'Group';
						$contractType = prepareInput($contractType);
					}
				}
				else {
					$contractType = 'None';
					$contractType = prepareInput($contractType);
				}
				oci_free_statement($contractTypeQuery);
			}
		}
		oci_free_statement($serviceContractQuery);
	}
	else {
		$price = randomFloat(100,500);
		$price = round($price,2);
		$contractType = 'None';
	}

	$customerQuery = oci_parse($conn,"Select name from Customers where name = :name and contactInfo = :contactInfo");
	oci_bind_by_name($customerQuery, ':name', $customerName);
	oci_bind_by_name($customerQuery, ':contactInfo', $contactInfo);
	oci_execute($customerQuery);
	if(!oci_fetch($customerQuery)) {
		insertCustomerIntoDB($customerName,$contactInfo);
	}
	oci_free_statement($customerQuery);
	
	insertItemIntoDB($customerName,$contactInfo,$contractId,$type,$model,$price,$year,$contractType);
	




	
}

function randomFloat($min = 100, $max = 500) {
    return $min + mt_rand() / mt_getrandmax() * ($max - $min);
}
function prepareInput($inputData){
	$inputData = trim($inputData);
  	$inputData  = htmlspecialchars($inputData);
  	return $inputData;
}

function add_months($months, DateTime $dateObject) {
    $next = new DateTime($dateObject->format('Y-m-d'));
    $next->modify('last day of +'.$months.' month');

    if($dateObject->format('d') > $next->format('d')) {
        return $dateObject->diff($next);
    } 
    else {
            return new DateInterval('P'.$months.'M');
    }
}

function advanceDate($d1, $months){
    $date = new DateTime($d1);

    // call second function to add the months
    $newDate = $date->add(add_months($months, $date));

    // goes back 1 day from date, remove if you want same day of month
    $newDate->sub(new DateInterval('P1D')); 

    //formats final date to Y-m-d form
    $dateReturned = $newDate->format('Y-m-d'); 

    return $dateReturned;
}

function insertCustomerIntoDB($customerName,$contactInfo){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}


	$query = oci_parse($conn, "Insert Into Customers(name,contactInfo) values(:customerName,:contactInfo)");
	

	oci_bind_by_name($query, ':customerName', $customerName);
	oci_bind_by_name($query, ':contactInfo', $contactInfo);
	
	
	// Execute the query
	$res = oci_execute($query);

	if (!$res) {
		$e = oci_error($query); 
        	echo $e['Customer Already Exists or Invalid Data']; 
	}

	oci_free_statement($query);
	OCILogoff($conn);
}

function generateRepairId() {
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$repairIdQuery = oci_parse($conn, 'Select Count(*) AS "Counts" From RepairJob');
	oci_execute($repairIdQuery);
	oci_fetch($repairIdQuery);
	$rQueryResults = mt_rand(1,10000) + oci_result($repairIdQuery,"Counts");
	$repairId = "R" . $rQueryResults;
	oci_free_statement($repairIdQuery);

	return $repairId;
}

function insertRepairJobIntoDB($customerName,$contactInfo,$itemId,$contractId){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$repairId = generateRepairId();
	$rQuery = oci_parse($conn,"Select * from RepairJob where repairId = :repairId");
	oci_bind_by_name($rQuery, ':repairId', $repairId);
	oci_execute($rQuery);
	while(oci_fetch($rQuery) != false) {
		$repairId = generateRepairId();
		oci_execute($rQuery);
	}
	oci_free_statement($rQuery);

	$status = 'Under_Repair';
	$timeOfArrival = advanceDate(date("Y-m-d"), 1);
	$employeeNo = "E" . mt_rand(1,4);

	$query = oci_parse($conn, "Insert Into RepairJob(repairId,machineId,contractId,customerName,customerContact,timeOfArrival,status,employeeNo) values(:repairId,:itemId,:contractId,:customerName,:contactInfo,:timeOfArrival,:status,:employeeNo)");
	
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

	if ($res)
		echo '<br> Your RepairId is: ' . $repairId . "<br>" . "Your ItemId is: " . $itemId;
	else{
		$e = oci_error($query); 
        	echo $e['message']; 
	}

	oci_free_statement($query);
	OCILogoff($conn);
}

function generateItemId() {
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$itemIdQuery = oci_parse($conn, 'Select Count(*) AS "Counts" From RepairItems');
	oci_execute($itemIdQuery);
	oci_fetch($itemIdQuery);
	$iQueryResults = mt_rand(1,10000) + oci_result($itemIdQuery, "Counts");
	$itemId = "I" . $iQueryResults;
	oci_free_statement($itemIdQuery);

	return $itemId;
}

function insertItemIntoDB($customerName,$contactInfo,$contractId,$type,$model,$price,$year,$contractType){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$itemId = generateItemId();
	$iQuery = oci_parse($conn,"Select * from RepairItems where itemId = :itemId");
	oci_bind_by_name($iQuery, ':itemId', $itemId);
	oci_execute($iQuery);
	while(oci_fetch($iQuery) != false) {
		$itemId = generateItemId();
		oci_execute($iQuery);
	}
	oci_free_statement($iQuery);

	if(strcasecmp($contractId, 'None') != 0) {
		if(strcasecmp($contractType, 'Single') == 0) {
			$sContractQuery = oci_parse($conn, "Select * from SingleContract where contractId = :contract");
			oci_bind_by_name($sContractQuery, ':contract', $contractId);
			oci_execute($sContractQuery);
			if(!oci_fetch($sContractQuery)) {
				$insertQuery = oci_parse($conn,"Insert Into SingleContract(contractId,machineId,machineType)Values(:contractId,:itemId,:type)");
				oci_bind_by_name($insertQuery, ':contractId', $contractId);
				oci_bind_by_name($insertQuery, ':itemId', $itemId);
				oci_bind_by_name($insertQuery, ':type', $type);
				$error = oci_execute($insertQuery);
				if($error == false) {
						echo "Could not insert into SingleContract";
					}
				oci_free_statement($insertQuery);
			}
			oci_free_statement($sContractQuery);
		}
		else if (strcasecmp($contractType, 'Group') == 0){
			if(strcasecmp($type, 'Printer') != 0) {
				$gContractQuery = oci_parse($conn, "Select * from GroupContract where contractId = :contract");
				oci_bind_by_name($gContractQuery, ':contract', $contractId);
				oci_execute($gContractQuery);
				if(!oci_fetch($gContractQuery)) {
					$insertQuery = oci_parse($conn,"Insert Into GroupContract(contractId,computerId,printerId)Values(:contractId,'None',:printerId)");
					oci_bind_by_name($insertQuery, ':contractId', $contractId);
					oci_bind_by_name($insertQuery, ':printerId', $itemId);
					$error = oci_execute($insertQuery);
					if($error == false) {
						echo "Could not insert into GroupContract";
					}
					oci_free_statement($insertQuery);
				}
				oci_free_statement($gContractQuery);
			}
			else {
				$gContractQuery = oci_parse($conn, "Select * from GroupContract where contractId = :contract");
				oci_bind_by_name($gContractQuery, ':contract', $contractId);
				oci_execute($gContractQuery);
				if(!oci_fetch($gConractQuery)) {
					$insertQuery = oci_parse($conn,"Insert Into GroupContract(contractId,compterId,printerId)Values(:contractId,:computerId,'None')");
					oci_bind_by_name($insertQuery, ':contractId', $contractId);
					oci_bind_by_name($insertQuery, ':computerId', $itemId);
					$error = oci_execute($insertg2Query);
					if($error == false) {
						echo "Could not insert into GroupContract";
					}
					oci_free_statement($insertQuery);
				}
				oci_free_statement($gContractQuery);
			}
		}
	}
	

	$query = oci_parse($conn, "Insert Into RepairItems(itemId,contractId,type,model,price,year,serviceContractType)values(:itemId,:contractId,:type,:model,:price,:year,:serviceContractType)");
	
	oci_bind_by_name($query, ':itemId', $itemId);
	oci_bind_by_name($query, ':contractId', $contractId);
	oci_bind_by_name($query, ':type', $type);
	oci_bind_by_name($query, ':model', $model);
	oci_bind_by_name($query, ':year', $year);
	oci_bind_by_name($query, ':serviceContractType', $contractType);
	oci_bind_by_name($query, ':price', $price);
	


	// Execute the query
	$res = oci_execute($query);

	if ($res)
		echo '<br><br> <Item accepted, your ItemId is:' . $itemId;
	else{
		$e = oci_error($query); 
        	echo $e['message']; 
	}

	insertRepairJobIntoDB($customerName,$contactInfo,$itemId,$contractId);

	oci_free_statement($query);
	OCILogoff($conn);	
}



?>

</body>
</html>