CREATE OR REPLACE PACKAGE placement_pck
AS

PROCEDURE insert_comp(p_name company.companyname%TYPE
			p_sect company.sector%TYPE, p_size company.size%TYPE);

PROCEDURE delete_comp(p_id company.companyid%TYPE);

--CURSOR comp_placements_cur (p_comp_id IN company.companyid%TYPE);
--PROCEDURE query_comp_placements(p_id company.companyid%TYPE);

--PROCEDURE update_cur_row

END placement_pck;
/
SHOW ERRORS

CREATE OR REPLACE PACKAGE BODY placement_pck
AS

	PROCEDURE insert_comp(p_name company.companyname%TYPE
				p_sect company.sector%TYPE, p_size company.size%TYPE)
	IS
	BEGIN
    INSERT INTO company
    VALUES(
      company_sq.nextval,
      p_name,
      p_sect,
      p_size
    );
	END insert_comp;

	PROCEDURE delete_comp(p_id company.companyid%TYPE)
	IS
	BEGIN
		--to ensure references are deleted too ON DELETE CASCADE for FOREIGN KEYs
		DELETE * FROM comp 
		WHERE companyid = p_id;
	END delete_comp;

  --Return placements with no applicaitions
  PROCEDURE query_nil_app_placements()
  IS
  DECLARE
    CURSOR query_cur IS SELECT * FROM Application;
    NUMBER x;
  
  BEGIN
    OPEN query_cur;
    LOOP
      X = SELECT COUNT(*) INTO X
          FROM Application 
          WHERE PlacementID = query_cur.PlacementID;
                  
      IF X = 0
        FETCH query_cur INTO temp;
      END IF;
    END LOOP;
  END query_nil_app_placements;


--  PROCEDURE update_row()

END placement pck;
/
SHOW ERRORS