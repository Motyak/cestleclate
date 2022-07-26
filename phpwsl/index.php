<!-- php -S localhost:1337 index.php -->

<link href="https://unpkg.com/tailwindcss@^2/dist/tailwind.min.css" rel="stylesheet">
<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>

<?php
if(isset($_POST["explorer"]))
    exec("explorer.exe");
?>

<button type="button" class="bg-blue-500 hover:bg-blue-400 text-white font-bold text-9xl w-screen h-screen">OPEN EXPLORER</button>

<script>
	$("button").click(() => {
		$.post({data: {explorer: ''}});
	})
</script>
