<html>
<head></head>
<body>


<button style = "height:40px;width:200px" onclick="history.go(-1);">Back To Dashboard</button>
<br> <br>

<?php

showJobsUnderRepair();

function showJobsUnderRepair(){
	//connect to your database. Type in your username, password and the DB path
	$conn=oci_connect('dtaylor','Jenner96', '//dbserver.engr.scu.edu/db11g');
	if(!$conn) {
	     print "<br> connection failed:";       
        exit;
	}

	$query = oci_parse($conn, "Select * From RepairJob where status = 'Under_Repair'");
	
	// Execute the query
	$res = oci_execute($query);

	$counter = 1;
	while(($row = oci_fetch_array($query, OCI_BOTH)) != false) {
		$jobTitle = "Job " . $counter;
		echo "<strong>" . $jobTitle . "</strong> <br>";
		echo "Repair Id:" . $row['REPAIRID'] . "<br>" . "Machine Id: " . $row['MACHINEID'] . "<br>" . "Contract Id: ". $row['CONTRACTID'] . "<br>" . "Customer: ". $row['CUSTOMERNAME'] . "<br>" . "Contact Info: " .  $row['CUSTOMERCONTACT'] . "<br>" . "Brought in on: " . $row['TIMEOFARRIVAL'] . "<br><br>";
		$counter = $counter + 1;
	}

	oci_free_statement($query);
	OCILogoff($conn);
}



?>

</body>
</html>