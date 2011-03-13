-- Sequences similar behaviour to auto number. To be called on insertion
CREATE SEQUENCE student_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE company_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE contact_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE placement_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE application_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;

-- Add more simple constraints to tables
ALTER TABLE student
	ADD(
    CONSTRAINT student_pk PRIMARY KEY (studentid),
    CONSTRAINT student_no CHECK (
      REGEXP_LIKE(studentnumber, '[[:alpha:]]{3}[[:digit:]]{2}[[:alpha:]]{3}')),
    CONSTRAINT student_title CHECK (
      title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')),
    CONSTRAINT student_email CHECK (REGEXP_LIKE(emailaddress,'\@\'))
  )
;

ALTER TABLE company
  ADD(
    CONSTRAINT company_pk PRIMARY KEY (companyid),
    CONSTRAINT company_uq UNIQUE(companyname, sector),
    CONSTRAINT company_size CHECK ("Size" > '5'),
    CONSTRAINT company_sect CHECK (
      sector IN ('COMP', 'FINANCE', 'EDU', 'PUBLIC', 'OTHER')
    )
  )
;

ALTER TABLE contact
  ADD(
    CONSTRAINT contact_pk PRIMARY KEY (contactid),
    CONSTRAINT contact_fk FOREIGN KEY (companyid) REFERENCES company(companyid) ON DELETE CASCADE,
    CONSTRAINT contact_email CHECK (REGEXP_LIKE(email, '\@\')),
    CONSTRAINT contact_uq UNIQUE(email),
    CONSTRAINT contact_title CHECK (
      title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')
    )
  )
;

ALTER TABLE placement
  ADD(
    CONSTRAINT placement_pk PRIMARY KEY (placementid),
    CONSTRAINT placement_nopos CHECK (noofpositions > 0),
    CONSTRAINT placement_len CHECK (lengthmonths >= 3 AND lengthmonths <=15),
    CONSTRAINT placement_sal CHECK (salary >=0 AND salary <= 99999.99)
    --CONSTRAINT placement_sd CHECK (StartDate > (deadline + 730))
  )
;

ALTER TABLE placement_contacts
  ADD(
    CONSTRAINT placement_contacts_pk PRIMARY KEY (placementid, contactid),
    CONSTRAINT placement_contacts_fk1 FOREIGN KEY (placementid)
      REFERENCES placement(placementid) ON DELETE CASCADE,
    CONSTRAINT placement_contacts_fk2 FOREIGN KEY (contactid)
      REFERENCES contact(contactid) ON DELETE CASCADE
  )
;

ALTER TABLE application
  ADD(
    CONSTRAINT application_pk PRIMARY KEY (applicationid),
    CONSTRAINT application_fk1 FOREIGN KEY (studentid)
      REFERENCES student(studentid) ON DELETE CASCADE,
    CONSTRAINT application_fk2 FOREIGN KEY (placementid)
      REFERENCES placement(placementid) ON DELETE CASCADE,
    CONSTRAINT application_stat CHECK (status IN ('C','A','T','U','R'))
  )
;

ALTER TABLE stage_history
  ADD(
    CONSTRAINT stage_hist_pk PRIMARY KEY (applicationid, stagedate),
    CONSTRAINT stage_hist_fk FOREIGN KEY (applicationid) 
      REFERENCES application(applicationid) ON DELETE CASCADE
  )
;

--OK
-- placement insertion constraint for Deadline
CREATE OR REPLACE TRIGGER placement_insert
  BEFORE UPDATE ON placement
  FOR EACH ROW
  WHEN(NEW.deadline NOT BETWEEN SYSDATE AND (SYSDATE + 365))
  BEGIN
    raise_application_error(-3000, 'Deadline must be between now and 1 year from now');
  END placement_insert;
/

-- application update constraints
CREATE OR REPLACE TRIGGER application_update
  BEFORE UPDATE ON application
  FOR EACH ROW
--  WHEN(NEW.Status = 'C' OR NEW.Status = 'A')
  DECLARE x NUMBER;
  BEGIN
  IF (:NEW.status = 'C' OR :NEW.status = 'A')
  THEN
    SELECT count(*) INTO x
    FROM stage_history
    WHERE applicationid = :NEW.applicationid 
    AND status = :NEW.status;
    
    IF x >= 1
    THEN
      raise_application_error(-3001, 'Status already exists for application/student');
      --Update does not execute
    ELSE
      --Create Stage_history entry
      INSERT INTO stage_history
      VALUES(
      :NEW.applicationid, 
      SYSDATE, 
      :NEW.lastcompanyupdate, 
      :NEW.laststudentupdate,
      :NEW.stage,
      :NEW.status
      );
      --Update executes
    END IF;
  ELSE
      INSERT INTO stage_history
      VALUES(
      :NEW.applicationid, 
      SYSDATE, 
      :NEW.lastcompanyupdate, 
      :NEW.laststudentupdate,
      :NEW.stage,
      :NEW.status
      );
  END IF;
  END application_update;
/

CREATE OR REPLACE TRIGGER application_insert
  BEFORE INSERT ON application
  FOR EACH ROW
  DECLARE dl DATE;
    x NUMBER;
  BEGIN 
    --CHECK THE DEADLINE
    SELECT deadline INTO dl
    FROM placement
    WHERE placementid = :NEW.placementid;
  
    IF SYSDATE > dl
    THEN
      raise_application_error(-3002, 'Application too late');
    END IF;
  
    SELECT count(*) INTO x
    FROM application
    WHERE studentid = :NEW.studentid 
    AND status = 'A';
    
    IF x >= 1
    THEN
      raise_application_error(-3003, 'Already accepted placement');
    END IF;
    
          --Create Stage_history entry
      INSERT INTO stage_history
      VALUES(
      :NEW.applicationid, 
      SYSDATE, 
      :NEW.lastcompanyupdate, 
      :NEW.laststudentupdate,
      :NEW.stage,
      :NEW.status
      );
    
  END;
/