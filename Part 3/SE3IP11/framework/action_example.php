<?php
	$username = (isset($_POST['username'])) ? $_POST['username'] : null;
	
	$return = array();
	if($username != null)
	{
		include("functions.php");
		
		if(isUsernameUnique($username))
		{
			$return['status'] = 'OK';
	 	}
		else
		{
			$return['status'] = 'ERROR';
			$return['value'] = 'Username is taken';
		}
	}
	
	header('Content-Type: application/json; charset=utf-8');
	echo json_encode($return);


/*
	Returns either:
	
	{ 'status': 'OK' }
	
	or:
	
	{ 
		"status" : "ERROR",
		"value" : "Username is taken"
	}

*/
?>