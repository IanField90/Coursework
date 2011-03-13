CREATE OR REPLACE PACKAGE placement_pck
AS

PROCEDURE insert_comp(p_id company.companyid%TYPE, p_name company.companyname%TYPE
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

	PROCEDURE insert_comp(p_id company.companyid%TYPE, p_name company.companyname%TYPE
				p_sect company.sector%TYPE, p_size company.size%TYPE)
	IS

	BEGIN

	END insert_comp;

	PROCEDURE delete_comp(p_id company.companyid%TYPE)
	IS
	BEGIN
		--ensure references are deleted too. Larger task than bellow
		DELETE * FROM comp 
		WHERE companyid = p_id;
	END delete_comp;

END placement pck;
/
SHOW ERRORS