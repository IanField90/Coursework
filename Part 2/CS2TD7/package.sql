CREATE OR REPLACE PACKAGE placement_pck
AS

PROCEDURE insert_comp(p_id company.companyid%TYPE, p_name company.companyname%TYPE
			p_sect company.sector%TYPE, p_size company.size%TYPE);



END placement_pck;
/
SHOW ERRORS