/*
--reset
ROLLBACK;
DROP SEQUENCE student_sq;
DROP SEQUENCE company_sq;
DROP SEQUENCE contact_sq;
drop sequence PLACEMENT_SQ;
DROP SEQUENCE application_sq;
create sequence STUDENT_SQ increment by 1 start with 1 nomaxvalue nocycle cache 10;
create sequence COMPANY_SQ increment by 1 start with 1 nomaxvalue nocycle cache 10;
create sequence CONTACT_SQ increment by 1 start with 1 nomaxvalue nocycle cache 10;
create sequence PLACEMENT_SQ increment by 1 start with 1 nomaxvalue nocycle cache 10;
CREATE SEQUENCE application_sq INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE CACHE 10;
--*/

INSERT INTO student
VALUES 
(
  student_sq.nextval,
  'abc01ABC',
  'MR',
  'Ian',
  'Field',
  'dp005570@rdg.ac.uk',
  null
);

INSERT INTO student
VALUES
(
  student_sq.nextval,
  'abc02ABC',
  'MR',
  'Cool',
  'Man',
  'wicked@rdg.ac.uk',
  null
);

INSERT INTO company
VALUES(
  company_sq.nextval,
  'Oracle',
  'EDU',
  '5000'
);

INSERT INTO company
VALUES(
  company_sq.nextval,
  'Microsoft',
  'EDU',
  '5000'
);

INSERT INTO contact
VALUES(
  contact_sq.nextval,
  1,
  'MR',
  'Joe',
  'Bloggs',
  'Human resources',
  'Building 2',
  'Oracle way',
  'RG62ND',
  'joebloggs@oracle.com'
);

INSERT INTO contact
VALUES(
  contact_sq.nextval,
  2,
  'MR',
  'John',
  'Smith',
  'Human resources',
  'Building 2',
  'Microsoft way',
  'RG62ND',
  'JohnSmith@microsoft.com'
);

INSERT INTO placement
VALUES(
  placement_sq.nextval,
  'Developer',
  'Developing software applications',
  6,
  15000.00,
  to_date('2011/07/09', 'yyyy/mm/dd'),
  to_date('2011/08/09', 'yyyy/mm/dd'),
  3
);

INSERT INTO placement
VALUES(
  placement_sq.nextval,
  'Developer',
  'Developing Microsoft applications',
  13,
  18000.00,
  to_date('2011/07/09', 'yyyy/mm/dd'),
  to_date('2011/08/09', 'yyyy/mm/dd'),
  4
);

INSERT INTO placement_contacts
values(
  1,
  1
);

INSERT INTO placement_contacts
VALUES(
  2,
  2
);

INSERT INTO application
VALUES(
  application_sq.nextval,
  1,
  1,
  sysdate,
  sysdate,
  sysdate,
  'C',
  'S',
  null,
  null
);

INSERT INTO application
VALUES(
  application_sq.nextval,
  2,
  2,
  sysdate,
  sysdate,
  sysdate,
  'C',
  'S',
  null,
  null
);