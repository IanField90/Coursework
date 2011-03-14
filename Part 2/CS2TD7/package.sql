CREATE OR REPLACE PACKAGE placement_pck
AS

PROCEDURE insert_comp(p_name company.companyname%TYPE,
			p_sect company.sector%TYPE, p_size NUMBER);

PROCEDURE delete_comp(p_id company.companyid%TYPE);

PROCEDURE query_nil_app_placements;

END placement_pck;
/

--Populate the package body
CREATE OR REPLACE PACKAGE BODY placement_pck
AS

	PROCEDURE insert_comp(p_name company.companyname%TYPE,
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
		DELETE FROM company 
		WHERE companyid = p_id;
	END delete_comp;

  --Return placements with no applicaitions
  PROCEDURE query_nil_app_placements
  IS
    CURSOR query_cur IS SELECT * FROM Placement;
	X NUMBER;
	cur_row Placement%ROWTYPE;
  
  BEGIN
	DBMS_OUTPUT.enable();
    OPEN query_cur;
    LOOP
		FETCH query_cur INTO cur_row;
		SELECT COUNT(*) INTO X
          FROM Application 
          WHERE PlacementID = cur_row.PlacementID;
                  
      IF X = 0
	  THEN
        DBMS_OUTPUT.PUT_LINE('PlacementID: ' || cur_row.PlacementID || ' Position: ' || cur_row.PlacementID || ' Description: ' || cur_row.Description );
      END IF;
    END LOOP;
  END query_nil_app_placements;


--  PROCEDURE update_row()

END placement_pck;
/