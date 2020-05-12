<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>
      Access log
  </title>
</head>
<body>
	<?php
		$file = file_get_contents('/home/konsta/monproj/logs.txt', true);
	echo nl2br ($file);
	?>
</body>
</html>


