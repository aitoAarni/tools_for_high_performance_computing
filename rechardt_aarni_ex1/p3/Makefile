
target1: target2
	touch target1

target2: target3
	touch target2
 
target3: target1
	touch target3

.PHONY: clean
clean:
	rm -f target1 target2 target3