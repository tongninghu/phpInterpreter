<?php
	$username= "tongning";
	$password = 115823;
	$a = 4;
	$b = -1;
	$c;
	echo "in global a = ";
	echo $a;

	if ($username == "tongning") {
		$a = 2;
		echo "\nin if_statement a = ";
		echo $a;
	}

	function myTest($k) {
		$b = 2;
		if ($b > 0) {
			while ($k != 0) {
				$k = $k - 1;
				echo "\nin function k = ";
				echo $k;
			}
		}
	}

	echo "\nin global a = ";
	echo $a;
	echo "\nin global b = ";
	echo $b;

	myTest($a);
	myTest($a);

	echo "\nEnd\n";
?>
