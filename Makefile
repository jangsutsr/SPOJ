build:
	docker build -t spoj_gcc_img .

run:
	docker run --name SPOJ -dit -v $$PWD/:/SPOJ/ spoj_gcc_img

touch:
	touch $$PROBLEM_NAME.c
	touch inputs/$$PROBLEM_NAME.txt

remove:
	rm $$PROBLEM_NAME.c
	rm inputs/$$PROBLEM_NAME.txt

block:
	mv $$PROBLEM_NAME.c TODO/
	mv inputs/$$PROBLEM_NAME.txt TODO/

unblock:
	mv TODO/$$PROBLEM_NAME.c .
	mv TODO/$$PROBLEM_NAME.txt inputs/

exec:
	gcc -Wall -g $$PROBLEM_NAME.c -o bin/$$PROBLEM_NAME.exe
	bin/$$PROBLEM_NAME.exe < inputs/$$PROBLEM_NAME.txt

commit:
	git add .
	git commit -m "Create/update problem $$PROBLEM_NAME"
	git push origin master
