--Group: David Taylor


Drop Table CustomerBill;
Drop Table ProblemReport;
Drop Table RepairLog;
Drop Table RepairJob;
Drop Table RepairPerson;
Drop Table RepairItems;
Drop Table GroupContract;
Drop Table SingleContract;
Drop Table ServiceContract;
Drop Table Customers;


/* 
Decompositions / In BCNF or 3NF

Customers Table: 
	Primary Key: customerName, customerContact 
	No decomposition done
	In BCNF as both columns are the primary key

Service Contract Table, SingleContract, GroupContract:
	Broke into ServiceContract, SingleContract, and GroupContract from:
	ServiceContract(contractId,customerName,customerContact,startDate,endDate,contractType,singleItemId,groupItemId1,groupItemId2)
	
	Primary Keys: contractId
	Foreign Keys: customerName, customerContact

	FDS:
		contractId -> startDate,endDate,contractType,customerName,customerContact

	It is in BCNF

Repair Items Table:
	No decomposition
	Primary Key: itemId

	FDS:
		itemId -> contractId, type, model, year, price
		contractId -> serviceContractType

	Is in BCNF

RepairPerson Table:
	No decomposition
	Primary Key: employeeNo

	Fds:
		employeeNo -> name, phoneNo

	Is in BCNF

RepairJob Table:
	No decomposition
	Primary Key: repairId, machineId

	FDS:
		repairId,machineId -> contractId, customerName, customerContact, timeOfArrival, status, employeeNo
		machineId -> contractId
		repairId -> timeOfArrival, status, employeeNo

	In 3NF, but not BCNF

RepairLog Table:
	No decomposition
	Primary Key: repairId, machineId

	FDS:
		repairId, machineId -> contractId, customerName, customerContact, timeOfArrival, status, employeeNo
		machineId -> contractId

	In 3NF, but not BCNF

ProblemReport Table:
	No decomposition
	Primary Key: repairId, problemId
	
	In BCNF, both columns are the primary key

CustomerBill Table:
	No decompositions
	Primary Key: repairId, machineId
	Foreign Keys: customerName, customerContact,repairId,machineId

	FDS:
		repairId, machineId -> customerName, customerContact, model, employeeNo, timeIn, timeOut, laborHours, partCost, totalCost
		machineId -> model
		repairId -> customerName, customercontact, employeeNo, timeIn

	In 3NF, but not BCNF

*/




Create Table Customers(
	name varchar(25),
	contactInfo varchar(25),
	Primary Key(name, contactInfo)
);

Create Table ServiceContract(
	contractId varchar(25) Primary Key,
	customerName varchar(25),
	customerContact varchar(25),
	startDate varchar(25),
	endDate varchar(25),
	contractType varchar(6) CHECK(contractType IN ('Single','Group','None')),
	Constraint FK_ServiceContract Foreign Key (customerName,customerContact) references Customers(name,contactInfo)
);

Create Table SingleContract(
	contractId varchar(25) Primary Key,
	machineId varchar(25),
	machineType varchar(25) Check(machineType in ('Printer','Computer')),
	Foreign Key(contractId) references ServiceContract(contractId)
);

Create Table GroupContract(
	contractId varchar(25) Primary Key,
	computerId varchar(25),
	printerId varchar(25),
	Foreign Key(contractId) references ServiceContract(contractId)
);

Create Table RepairItems(
	itemId varchar(25) Primary Key,
	contractId varchar(25),
	type varchar(25),
	model varchar(25),
	price varchar(25),
	year varchar(25),
	serviceContractType varchar(6) CHECK(serviceContractType IN ('Single','Group','None'))
);

Create Table RepairPerson(
	employeeNo varchar(25) Primary Key,
	name varchar(25),
	phoneNo varchar(25)
);

Create Table RepairJob(
	repairId varchar(25) Primary Key,
	machineId varchar(25),
	contractId varchar(25) ,
	customerName varchar(25),
	customerContact varchar(25),
	timeOfArrival varchar(25),
	status varchar(12) Check(status In ('Under_Repair','Ready','Done')),
	employeeNo varchar(25),
	Foreign Key(machineId) references RepairItems(itemId),
	Constraint FK_RepairJob Foreign Key (customerName,customerContact) references Customers(name,contactInfo),
	Foreign Key(employeeNo) references RepairPerson(employeeNo)
);

Create Table RepairLog(
	repairId varchar(25),
	machineId varchar(25),
	contractId varchar(25) ,
	customerName varchar(25),
	customerContact varchar(25),
	timeOfArrival varchar(25),
	status varchar(4) Check(status IN ('Done')),
	employeeNo varchar(25),
	Primary Key(repairId, machineId)
);

Create Table ProblemReport(
	repairId varchar(25),
	problemId varchar(25),
	Primary Key(repairId,problemId)
);

Create Table CustomerBill(
	repairId varchar(25),
	machineId varchar(25),
	customerName varchar(25),
	customerContact varchar(25),
	model varchar(25),
	employeeNo varchar(25),
	timeIn varchar(25),
	timeOut varchar(25),
	laborHours varchar(25),
	partCost float(2),
	totalCost float(2),
	Primary Key(repairId, machineId),
	Constraint FK_Bill Foreign Key (customerName,customerContact) references Customers(name,contactInfo),
	Constraint FK2_Bill Foreign Key(repairId, machineId) references RepairLog(repairId,machineId)
);

