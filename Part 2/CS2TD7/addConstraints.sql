-- Sequences similar behaviour to auto number. To be called on insertion
CREATE SEQUENCE student_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE company_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE contact_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE placement_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;

-- Add more simple constraints to tables
ALTER TABLE student
	ADD(
    CONSTRAINT student_pk PRIMARY KEY (StudentID),
    CONSTRAINT student_no CHECK (
      regexp_like(StudentNumber, '[:alpha:]{3}[:digit:]{2}[:alpha:]{3}')),
    CONSTRAINT student_title CHECK (
      Title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')),
    CONSTRAINT student_email CHECK (regexp_like(EmailAddress,'\W@\W'))
  )
;

ALTER TABLE company
  ADD(
    CONSTRAINT company_pk PRIMARY KEY (CompanyID),
    CONSTRAINT company_uq UNIQUE(CompanyName, Sector),
    CONSTRAINT company_size CHECK ('Size' > '5'),
    CONSTRAINT company_sect CHECK (
      'Sector' IN ('Comp', 'Finance', 'Edu', 'Public', 'Other')
    )
  )
;

ALTER TABLE contact
  ADD(
    CONSTRAINT contact_pk PRIMARY KEY (ContactID),
    CONSTRAINT contact_fk FOREIGN KEY (CompanyID) REFERENCES company(CompanyID),
    CONSTRAINT contact_email CHECK (regexp_like(email, '\W@\W')),
    CONSTRAINT contact_uq UNIQUE(email),
    CONSTRAINT contact_title CHECK (
      Title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')
    )
  )
;

ALTER TABLE placement
  ADD(
    CONSTRAINT placement_pk PRIMARY KEY (PlacementID),
    CONSTRAINT placement_nopos CHECK (NoOfPositions > 0),
    CONSTRAINT placement_len CHECK (LengthMonths >= 3 AND LengthMonths <=15),
    CONSTRAINT placement_sal CHECK (Salary >=0 AND Salary <= 99999.99),
    CONSTRAINT placement_sd CHECK (StartDate > (deadline + 730))
  )
;

ALTER TABLE placement_contacts
  ADD(
    CONSTRAINT placement_contacts_pk PRIMARY KEY (PlacementID, ContactID),
    CONSTRAINT placement_contacts_fk1 FOREIGN KEY (PlacementID)
      REFERENCES placement(PlacementID),
    CONSTRAINT placement_contacts_fk2 FOREIGN KEY (ContactID)
      REFERENCES contact(ContactID)
  )
;

ALTER TABLE application
  ADD(
    CONSTRAINT application_pk PRIMARY KEY (ApplicationID),
    CONSTRAINT application_fk1 FOREIGN KEY (StudentID)
      REFERENCES student(StudentID),
    CONSTRAINT application_fk2 FOREIGN KEY (PlacementID)
      REFERENCES placement(PlacementID),
    CONSTRAINT application_stat CHECK (Status IN ('C','A','T','U','R'))
  )
;

ALTER TABLE stage_history
  ADD(
    CONSTRAINT stage_hist_pk PRIMARY KEY (ApplicationID, StageDate),
    CONSTRAINT stage_hist_fk FOREIGN KEY (ApplicationID) 
      REFERENCES application(ApplicationID)
  )
;

-- placement insertion constraint for Deadline
CREATE OR REPLACE TRIGGER placement_insert
  BEFORE UPDATE ON placement
  FOR EACH ROW
  WHEN(NEW.deadline NOT BETWEEN sysdate AND (sysdate + 365))
  BEGIN
    RAISE_APPLICATION_ERROR(-3000, 'Deadline must be between now and 1 year from now');
  END placement_insert;
/

-- application update constraints
CREATE OR REPLACE TRIGGER application_update
  BEFORE UPDATE ON application
  FOR EACH ROW
  WHEN(NEW.Status = 'C' OR NEW.Status = 'A')
  DECLARE X NUMBER;
  BEGIN
    SELECT COUNT(*) INTO X
    FROM stage_history
    WHERE ApplicationID = :NEW.ApplicationID 
    AND Status = :NEW.Status;
    
    IF X >= 1
    THEN
      RAISE_APPLICATION_ERROR(-3001, 'Status already exists for application/student');
      --Update does not execute
    ELSE
      --Create Stage_history entry
      INSERT INTO stage_history
      VALUES(
      :NEW.ApplicationID, 
      sysdate, 
      :NEW.LastCompanyUpdate, 
      :NEW.LastStudentUpdate,
      :NEW.Stage,
      :NEW.Status
      );
      --Update executes
    END IF;
  END application_update;
/

CREATE OR REPLACE TRIGGER application_insert
  BEFORE INSERT ON application
  FOR EACH ROW
  DECLARE dl DATE;
    X NUMBER;
  BEGIN 
    --CHECK THE DEADLINE
    SELECT Deadline INTO dl
    FROM Placement
    WHERE PlacementID = :NEW.PlacementID;
  
    IF sysdate > dl
    THEN
      RAISE_APPLICATION_ERROR(-3002, 'Application too late');
    END IF;
  
    SELECT COUNT(*) INTO X
    FROM application
    WHERE StudentID = :NEW.StudentID 
    AND Status = 'A';
    
    IF X >= 1
    THEN
      RAISE_APPLICATION_ERROR(-3003, 'Already accepted placement');
    END IF;
    
  END;
/