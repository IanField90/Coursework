/* Sequences similar behaviour to auto number. To be called on insertion */
CREATE SEQUENCE student_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE company_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE contact_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE placement_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;

/* Triggers for date constraints on insertion and updates */
CREATE OR REPLACE TRIGGER application_app_date
  BEFORE INSERT ON application
  FOR EACH ROW
BEGIN
    IF (:new.DateOfApplication > (SELECT Deadline FROM placement WHERE PlacementID = :new.PlacementID))
    THEN
      INSERT INTO application (ApplicationID, StudentID, PlacementID, DateOfApplication, 
        LastCompanyUpdate, LastStudentUpdate, Status, Stage, Notes, CoverLetter)
      VALUES (:new.ApplicationID, :new.StudentID, :new.PlacementID, :new.DateOfApplication, 
        :new.LastCompanyUpdate, :new.LastStudentUpdate, :new.Status, 
        :new.Stage, :new.Notes, :new.CoverLetter)
    END IF;
END;


/* Add constraints to tables */
ALTER TABLE student
	CONSTRAINT student_pk PRIMARY KEY (StudentID),
  CONSTRAINT student_no CHECK (regexp_like(StudentNo, '[:alpha:]{3}[:digit:]{2}[:alpha:]{3}')),
	CONSTRAINT student_title CHECK (Title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')),
	CONSTRAINT student_email CHECK (regexp_like(email,'\W@\W')
;

ALTER TABLE company
	CONSTRAINT company_pk PRIMARY KEY (CompanyID),
  CONSTRAINT company_uq UNIQUE(CompanyID, Sector),
  CONSTRAINT company_sz CHECK ('Size' > 5),
	CONSTRAINT company_sect CHECK (Sector IN ('Comp', 'Finance', 'Edu', 'Public', 'Other'))
;

ALTER TABLE contact
	CONSTRAINT contact_pk PRIMARY KEY (ContactID),
	CONSTRAINT contact_fk FOREIGN KEY (CompanyID) REFERENCES company(CompanyID),
  CONSTRAINT contact_email CHECK (regexp_like(email, '\W@\W'),
  CONSTRAINT contact_uq UNIQUE(email),
	CONSTRAINT contact_title CHECK (Title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER'))
;

ALTER TABLE placement
	CONSTRAINT placement_pk PRIMARY KEY (PlacementID),
  CONSTRAINT placement_nopos CHECK (NoOfPositions > 0),
  CONSTRAINT placement_len CHECK (LengthMonths >= 3 AND LengthMonths <=15),
  CONSTRAINT placement_sal CHECK (Salary >=0 AND Salary <= 99999.99),
  /* Date constraints */
  CONSTRAINT placement_dl CHECK (deadline > sysdate AND deadline <= (sysdate + interval '1' year)),
  CONSTRAINT placement_sd CHECK (StartDate > (deadline + interval '2' years))
;

ALTER TABLE placement_contacts
	CONSTRAINT placements_contacts_pk PRIMARY KEY (PlacementID AND ContactID),
	CONSTRAINT placements_contacts_fk1 FOREIGN KEY (PlacementID) REFERENCES placement(PlacementID),
	CONSTRAINT placements_contacts_fk2 FOREIGN KEY (ContactID) REFERENCES contact(ContactID)
;

ALTER TABLE application
  CONSTRAINT application_pk PRIMARY KEY (ApplicationID),
  CONSTRAINT application_fk1 FOREIGN KEY (StudentID) REFERENCES student(StudentID),
  CONSTRAINT application_fk2 FOREIGN KEY (PlacementID) REFERENCES placement(PlacementID),
  CONSTRAINT application_dte CHECK (DateOfApplication <= (SELECT Deadline FROM placement 
                WHERE placmentID = application.PlacementID),
  /*If student has accepted another placement, cannot create. Can't accept more than 1, 
  Application can't return to 'current'*/
	CONSTRAINT application_stat CHECK (Status IN ('C','A','T','U','R')),
;

ALTER TABLE stage_history
  CONSTRAINT stage_hist_pk PRIMARY KEY (ApplicationID AND StageDate),
  CONSTRAINT stage_hist_fk FOREIGN KEY (ApplicationID) REFERENCES application(ApplicationID),
;