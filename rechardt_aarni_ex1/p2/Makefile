text  := Just some text to fill out the blank files that are created for this exercise, this text isn't necesasry, but is here to illustrate some data that could be in a file that will be create during the execution of this exercise.

copies := dep_2a dep_2b

target: ${copies}
	cat dep_2a > target
	cat dep_2b >> target

dep_2a: dep_1a
	cp dep_1a dep_2a

dep_2b: dep_1b
	cp dep_1b dep_2b

dep_1a:
	echo "${text}" > dep_1a

dep_1b:
	echo "${text}" > dep_1b

.PHONY: clean
clean:
	rm -f target dep*