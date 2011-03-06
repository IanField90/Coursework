ALTER TABLE student
	CONSTRAINT student_pk PRIMARY KEY (StudentID)
;


ALTER TABLE company
	CONSTRAINT company_pk PRIMARY KEY (CompanyID)
;

ALTER TABLE contact
	CONSTRAINT contact_pk PRIMARY KEY (ContactID)
	CONSTRAINT contact_fk FOREIGN KEY (CompanyID) REFERENCES company(CompanyID)
;

ALTER TABLE placement
	CONSTRAINT placement_pk PRIMARY KEY ( company AND 'role')
;

ALTER TABLE placement_contacts
	CONSTRAINT placements_contacts_pk PRIMARY KEY (PlacementID AND ContactID)
	CONSTRAINT placements_contacts_fk1 FOREIGN KEY (PlacementID) REFERENCES placement(PlacementID)
	CONSTRAINT placements_contacts_fk2 FOREIGN KEY (ContactID) REFERENCES contact(ContactID)
;

ALTER TABLE application
;

ALTER TABLE stage_history
;