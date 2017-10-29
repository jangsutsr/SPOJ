build:
	docker build -t spoj_gcc_img .

run:
	docker run --name SPOJ -dit -v $$PWD/:/SPOJ/ spoj_gcc_img

exec:
	gcc -Wall -g $$PROBLEM_NAME.c -o bin/$$PROBLEM_NAME.exe
	bin/$$PROBLEM_NAME.exe < inputs/$$PROBLEM_NAME.txt

commit:
	git add .
	git commit -m "Create/update problem $$PROBLEM_NAME"
	git push origin master
