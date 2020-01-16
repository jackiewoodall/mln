mln: mln.c
	clang -o mln mln.c

test:
	echo 0; ./mln 9 0
	echo 72; ./mln 9 8
	echo 891; ./mln 99 9
	echo 1524157875019052100; ./mln 1234567890 1234567890

