CREATE TABLE student(
	StudentID VARCHAR2(8),
	StudentNUMBER integer,
	Title varchar(5),
	FirstName VARCHAR2(60), 
	LastName VARCHAR2(60), 
	EmailAddress VARCHAR2(100), 
	CV BLOB
);

CREATE TABLE company(
	CompanyID NUMBER(5),
	CompanyName VARCHAR2(50), 
	Sector VARCHAR2(7), 
	'Size' VARCHAR2(11),
);

CREATE TABLE contact(
	ContactID NUMBER(5),
	CompanyID NUMBER(5),
	Title VARCHAR2(5), 
	FirstName VARCHAR2(60), 
	Surname VARCHAR2(60), 
	Position VARCHAR2(60),
	AddressLine1 VARCHAR2(120),
	AddressLine2 VARCHAR2(120),
	PostCode VARCHAR2(8), 
	Email VARCHAR2(100),
);

CREATE TABLE placement (
	PlacementID NUMBER(5),
	Position VARCHAR2(60),
	Description VARCHAR2(150),
	LengthMonths NUMBER(2),
	Salary NUMBER(7,2),
	Deadline DATE,
	StartDate DATE,
	NoOfPositions NUMBER(3)
);

CREATE TABLE placement_contacts(
	PlacementID NUMBER(5),
	ContactID NUMBER(5)
);

CREATE TABLE application(
	ApplicationID NUMBER(5),
	StudentID VARCHAR2(7),
	PlacementID NUMBER(5),
	DateOfApplication DATE DEFAULT sysdate,
	LastCompanyUpdate DATE,
	LastStudentUpdate DATE,
	Status VARCHAR2(1) DEFAULT 'C' NOT NULL,
	Stage VARCHAR2(1) DEFAULT 'S' NOT NULL,
	Notes VARCHAR2(250),
	CoverLetter BLOB
);

CREATE TABLE stage_history(
  ApplicationID NUMBER(5),
	StageDate DATE DEFAULT (SELECT FROM application WHERE ApplicationID = stage_history.ApplicationID),
	CompanyUpdate DATE,
	StudentUpdate DATE,
	Stage VARCHAR2(20),
	Status VARCHAR2(1)
);
