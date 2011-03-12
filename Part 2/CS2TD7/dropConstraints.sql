ALTER TRIGGER application_insert DISABLE;
ALTER TRIGGER application_update DISABLE;
ALTER TRIGGER placement_insert DISABLE;

DROP SEQUENCE student_sq;
DROP SEQUENCE company_sq;
DROP SEQUENCE contact_sq;
DROP SEQUENCE placement_sq;
DROP SEQUENCE application_sq;

-- Drop foreign keys first
ALTER TABLE application DROP CONSTRAINT application_fk1;
ALTER TABLE application DROP CONSTRAINT application_fk2;
ALTER TABLE placement_contacts DROP CONSTRAINT placement_contacts_fk1;
ALTER TABLE placement_contacts DROP CONSTRAINT placement_contacts_fk2;
ALTER TABLE stage_history DROP CONSTRAINT stage_hist_fk;
ALTER TABLE contact DROP CONSTRAINT contact_fk;

ALTER TABLE student DROP CONSTRAINT student_pk;
ALTER TABLE student DROP CONSTRAINT student_no;
ALTER TABLE student DROP CONSTRAINT student_title;
ALTER TABLE student DROP CONSTRAINT student_email;

ALTER TABLE company DROP CONSTRAINT company_uq;
ALTER TABLE company DROP CONSTRAINT company_size;
ALTER TABLE company DROP CONSTRAINT company_sect;

ALTER TABLE contact DROP CONSTRAINT contact_pk;
ALTER TABLE contact DROP CONSTRAINT contact_email;
ALTER TABLE contact DROP CONSTRAINT contact_uq;
ALTER TABLE contact  DROP CONSTRAINT contact_title;

ALTER TABLE placement DROP CONSTRAINT placement_pk;
ALTER TABLE placement DROP CONSTRAINT placement_nopos;
ALTER TABLE placement DROP CONSTRAINT placement_len;
ALTER TABLE placement DROP CONSTRAINT placement_sal;
--ALTER TABLE placement DROP CONSTRAINT placement_sd;

ALTER TABLE placement_contacts DROP CONSTRAINT placement_contacts_pk;

ALTER TABLE application DROP CONSTRAINT application_pk;
ALTER TABLE application DROP CONSTRAINT application_stat;

ALTER TABLE stage_history DROP CONSTRAINT stage_hist_pk;

ALTER TABLE company DROP CONSTRAINT company_pk;