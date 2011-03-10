-- Sequences similar behaviour to auto number. To be called on insertion
CREATE SEQUENCE student_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE company_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE contact_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
CREATE SEQUENCE placement_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;

-- Add simple constraints to tables 
ALTER TABLE student
	ADD(
		CONSTRAINT student_pk PRIMARY KEY (StudentID),
		CONSTRAINT student_no CHECK (
			regexp_like(StudentNo, '[:alpha:]{3}[:digit:]{2}[:alpha:]{3}')),
		CONSTRAINT student_title CHECK (
			Title IN ('MR','MRS','DR', 'PROF', 'MISS', 'MS', 'OTHER')),
		CONSTRAINT student_email CHECK (regexp_like(email,'\W@\W')
	)
;

ALTER TABLE company
	ADD(
		CONSTRAINT company_pk PRIMARY KEY (CompanyID),
		CONSTRAINT company_uq UNIQUE(CompanyID, Sector),
		CONSTRAINT company_sz CHECK ('Size' > 5),
		CONSTRAINT company_sect CHECK (
			Sector IN ('Comp', 'Finance', 'Edu', 'Public', 'Other')
		)
	)
;

ALTER TABLE contact
	ADD(
		CONSTRAINT contact_pk PRIMARY KEY (ContactID),
		CONSTRAINT contact_fk FOREIGN KEY (CompanyID) REFERENCES company(CompanyID),
		CONSTRAINT contact_email CHECK (regexp_like(email, '\W@\W'),
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
		CONSTRAINT placement_dl CHECK (
			deadline > sysdate AND deadline <= (sysdate + interval '1' year)
		),
		CONSTRAINT placement_sd CHECK (StartDate > (deadline + interval '2' years))
	)
;

ALTER TABLE placement_contacts
	ADD(
		CONSTRAINT placements_contacts_pk PRIMARY KEY (PlacementID AND ContactID),
		CONSTRAINT placements_contacts_fk1 FOREIGN KEY (PlacementID)
			REFERENCES placement(PlacementID),
		CONSTRAINT placements_contacts_fk2 FOREIGN KEY (ContactID)
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
		CONSTRAINT application_dte CHECK (
			DateOfApplication <= (SELECT Deadline FROM placement 
			WHERE placmentID = application.PlacementID
		),
		CONSTRAINT application_stat CHECK (Status IN ('C','A','T','U','R'))
	)
;

ALTER TABLE stage_history
	ADD(
		CONSTRAINT stage_hist_pk PRIMARY KEY (ApplicationID AND StageDate),
		CONSTRAINT stage_hist_fk FOREIGN KEY (ApplicationID) 
			REFERENCES application(ApplicationID)
	)
;


-- #### Complex constraints ###
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
			WHERE PlacementID = :NEW.PlacementID

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
