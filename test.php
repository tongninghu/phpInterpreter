<?php
	$username= "tongning";
	$password = 115823;
	$a = 4;
	if ($username == "tongning") {
		$a = $a + 1;
	}

	function myTest($k) {
		if ($k > 0) {
			while ($k != 0) {
				$k = $k - 1;
			}
		}
	}

	myTest($a);
?>
