<html>
<head></head>
<body>


<button style = "height:40px;width:200px" onclick="history.go(-1);">Back </button>
<br> <br>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // collect input data
	
	$startDate= $_POST['startDate'];
	$endDate= $_POST['endDate'];

	if(empty($endDate) || empty($endDate)) {
		die(header("location:revenueGenerated.html?noInfo=true"));
	}

	$sDate = new DateTime($startDate);
	$eDate = new DateTime($endDate);

	revenue($sDate,$eDate);
    
}

function prepareInput($inputData){
	$inputData = trim($inputData);
  	$inputData  = htmlspecialchars($inputData);
  	return $inputData;
}

function revenue($sDate,$eDate) {
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}
	$revenue = 0;
	$coveredWarranty = 0;
	$query = oci_parse($conn,"Select * from CustomerBill");
	oci_execute($query);
	while(($row = oci_fetch_array($query, OCI_BOTH)) != false) {
		$dataDate = new DateTime($row['TIMEOUT']);
		$partCost = $row['PARTCOST'];
		$totalCost = $row['TOTALCOST'];

		if($dataDate > $sDate && $dataDate < $eDate) {
			if($totalCost == 0) {
				$coveredWarranty = $coveredWarranty + $partCost;
			}
			else {
				$revenue = $revenue + $totalCost;
			}
		}
	}

	echo "<strong>Revenue Earned:</strong> $" . $revenue . "<br>" . "<strong>Amount Covered by Warranty:</strong> $" . $coveredWarranty . "<br>";
}

?>

</body>
</html>