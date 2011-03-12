DROP TABLE student;
CREATE TABLE student(
	StudentID NUMBER(5),
	StudentNUMBER VARCHAR2(8) NOT NULL,
	Title varchar(5) NOT NULL,
	FirstName VARCHAR2(60) NOT NULL, 
	LastName VARCHAR2(60) NOT NULL, 
	EmailAddress VARCHAR2(100) NOT NULL, 
	CV BLOB
);

DROP TABLE company;
CREATE TABLE company(
	CompanyID NUMBER(5),
	CompanyName VARCHAR2(50) NOT NULL, 
	Sector VARCHAR2(7) NOT NULL, 
	"Size" VARCHAR2(11) NOT NULL
);

DROP TABLE contact;
CREATE TABLE contact(
	ContactID NUMBER(5),
	CompanyID NUMBER(5),
	Title VARCHAR2(5) NOT NULL, 
	FirstName VARCHAR2(60), 
	Surname VARCHAR2(60) NOT NULL, 
	Position VARCHAR2(60) NOT NULL,
	AddressLine1 VARCHAR2(120) NOT NULL,
	AddressLine2 VARCHAR2(120) NOT NULL,
	PostCode VARCHAR2(8) NOT NULL, 
	Email VARCHAR2(100)
);

DROP TABLE placement;
CREATE TABLE placement (
	PlacementID NUMBER(5),
	Position VARCHAR2(60) NOT NULL,
	Description VARCHAR2(150) NOT NULL,
	LengthMonths NUMBER(2) NOT NULL,
	Salary NUMBER(7,2) NOT NULL,
	Deadline DATE NOT NULL,
	StartDate DATE NOT NULL,
	NoOfPositions NUMBER(3) NOT NULL
);

DROP TABLE placement_contacts;
CREATE TABLE placement_contacts(
	PlacementID NUMBER(5),
	ContactID NUMBER(5)
);

DROP TABLE application;
CREATE TABLE application(
	ApplicationID NUMBER(5),
	StudentID NUMBER(5),
	PlacementID NUMBER(5),
	DateOfApplication DATE DEFAULT sysdate,
	LastCompanyUpdate DATE NOT NULL,
	LastStudentUpdate DATE NOT NULL,
	Status VARCHAR2(1) DEFAULT 'C' NOT NULL,
	Stage VARCHAR2(1) DEFAULT 'S' NOT NULL,
	Notes VARCHAR2(250),
	CoverLetter BLOB
);

DROP TABLE stage_history;
CREATE TABLE stage_history(
  ApplicationID NUMBER(5),
	StageDate DATE,
	CompanyUpdate DATE,
	StudentUpdate DATE,
	Stage VARCHAR2(20),
	Status VARCHAR2(1)
);
