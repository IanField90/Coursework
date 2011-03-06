CREATE TABLE student(
	StudentID varchar2(8),
	StudentNumber integer,
	Title varchar(5),
	FirstName varchar2(60), 
	LastName varchar2(60), 
	EmailAddress varchar2(100), 
	CV BLOB
);

CREATE TABLE company(
	CompanyID Number(5),
	CompanyName varchar2(50), 
	Sector varchar2(7), 
	'Size' Char(11),
);

CREATE TABLE contact(
	ContactID Number(5),
	CompanyID Number(5),
	Title varchar2(5), 
	FirstName varchar2(60), 
	Surname varchar2(60), 
	Position varchar2(60),
	AddressLine1 varchar2(120),
	AddressLine2 varchar2(120),
	PostCode varchar2(8), 
	Email varchar2(100),
);

CREATE TABLE placement (
	PlacementID Number(5),
	Position varchar2(60),
	Description varchar2(150),
	LengthMonths Number(2),
	Salary Number(7.2),
	Deadline DATE,
	StartDate DATE,
	NoOfPositions Number(3),
);

CREATE TABLE placement_contacts(
	PlacementID Number(5),
	ContactID Number(5)
);

CREATE TABLE application(
	ApplicationID Number(5),
	StudentID varchar2(7),
	PlacementID Number(5),
	DateOfApplication DATE,
	LastCompanyUpdate DATE,
	LastStudentUpdate DATE,
	Notes varchar2(250),
	CoverLetter BLOB
);

CREATE TABLE stage_history(
	StageDate DATE,
	CompanyUpdate DATE,
	StudentUpdate DATE,
	Stage varchar2(20),
	Status char
);

