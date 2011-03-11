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

--Date Error
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

/*

-- application date check
    /*
    CONSTRAINT application_date CHECK (
      DateOfApplication <= (SELECT Deadline FROM placement 
      WHERE placmentID = application.PlacementID
    ),*/
    
-- placement deadline date check
--CONSTRAINT placement_dl CHECK (deadline BETWEEN sysdate AND (dealine + 365))

-- application update constraints
CREATE OR REPLACE TRIGGER application_update
  BEFORE UPDATE ON application
  FOR EACH ROW
  BEGIN
    IF(:NEW.Status = 'C' OR :NEW.Status = 'A')
      THEN
        --If stage_history has C or A under status for placementID
        IF(NUM_ROWS(SELECT Stage FROM stage_history 
            WHERE PlacementID = NEW.PlacementID AND Status = NEW.Status) = 1)
          --Block 'C' and 'A'
          NULL
        ELSE
          --Do update
          UPDATE TABLE application
          SET Status = :NEW.Status
          WHERE PlacementID = NEW.PlacementID
          
          --Create Stage_history entry
          INSERT INTO stage_history
          VALUES(
          :NEW.ApplicationID, 
          :NEW.StageDate, 
          :NEW.CompanyUpdate, 
          :NEW.StudentUpdate,
          :NEW.Stage,
          :NEW.Status
          );
        END IF;
    ELSE
      --Do update regardless
      
      --Create Stage_history entry
      INSERT INTO stage_history
      VALUES(
      :NEW.ApplicationID, 
      :NEW.StageDate, 
      :NEW.CompanyUpdate, 
      :NEW.StudentUpdate,
      :NEW.Stage,
      :NEW.Status
      );
    END IF;
  END;

-- Application insert constraint
-- Student cannot have more than one appication 'C'
CREATE OR REPLACE TRIGGER application_insert
  BEFORE INSERT ON application
  FOR EACH ROW
  BEGIN
    --If student already has placementID with status 'A' block insert
    IF(NUM_ROWS(SELECT * FROM application WHERE StudentID = NEW.StudentID AND Status = 'A') = 1)
      THEN
        NULL
      ELSE
      -- Perform Insertion
      INSERT INTO application
      VALUES(
      
      );
    END IF;
  
    --Create Stage_history entry
    INSERT INTO stage_history
    VALUES(
    :NEW.ApplicationID, 
    :NEW.StageDate, 
    :NEW.CompanyUpdate, 
    :NEW.StudentUpdate,
    :NEW.Stage,
    :NEW.Status
    );
  END;
  */