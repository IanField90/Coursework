ALTER TRIGGER application_insert DISABLE;
ALTER TRIGGER application_update DISABLE;

ALTER TABLE student
	DROP CONSTRAINT student_pk,
	DROP CONSTRAINT student_no,
	DROP CONSTRAINT student_title,
	DROP CONSTRAINT student_email
;

ALTER TABLE company
	DROP CONSTRAINT company_pk,
	DROP CONSTRAINT company_uq,
	DROP CONSTRAINT company_size,
	DROP CONSTRAINT company_sect
;

ALTER TABLE contact
	DROP CONSTRAINT contact_pk,
	DROP CONSTRAINT contact_fk,
	DROP CONSTRAINT contact_email,
	DROP CONSTRAINT contact_uq,
	DROP CONSTRAINT contact_title
;

ALTER TABLE placement
	DROP CONSTRAINT placement_pk,
	DROP CONSTRAINT placement_nopos,
	DROP CONSTRAINT placement_len,
	DROP CONSTRAINT placement_sal,
	DROP CONSTRAINT placement_dl,
	DROP CONSTRAINT placement_sd
;

ALTER TABLE placement_contacts
	DROP CONSTRAINT placement_contacts_pk,
	DROP CONSTRAINT placement_contacts_fk1,
	DROP CONSTRAINT placement_contacts_fk2
;

ALTER TABLE application
	DROP CONSTRAINT application_pk,
	DROP CONSTRAINT application_fk1,
	DROP CONSTRAINT application_fk2,
	DROP CONSTRAINT application_date,
	DROP CONSTRAINT application_stat
;

ALTER TABLE stage_history
	DROP CONSTRAINT stage_hist_pk,
	DROP CONSTRAINT stage_hist_fk
;