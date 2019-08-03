<?php
	$username = "tongning";
	$password = 115823;
	$a = 4;
	$b = -1;
	$c;

	echo "\nin global, a = ";
	echo $a;

	if ($username == "yunfeng") {
		echo "\nenter if";
	}
	else if ($username == "tongning") {
		$a = $b + 1;
		echo "\nenter else if, a = ";
		echo $a;
	}
	else {
		echo "\nenter else";
	}

	echo "\nin global, a = ";
	echo $a;

	function myTest($k) {
		$b = 2;
		if ($b == -1) {
			while ($k != 0) {
				$k = $k - 1;
				echo "\nin function, k = ";
				echo $k;
			}
		}
		else {
			while ($k < 5) {
				$k = $k + 1;
				echo "\nin function, k = ";
				echo $k;
			}
		}
	}

	myTest($a);

	echo "\nin global, b = ";
	echo $b;

	myTest($b);

	echo "\nEnd\n";
?>
