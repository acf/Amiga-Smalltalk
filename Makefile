check: ast_tests
	./ast_tests

.PHONY: check

ast_tests: ObjectMemory.c ObjectMemory.h ObjectMemoryTests.c ObjectMemoryTests.h vm_tests.c tests.h
	gcc -ggdb ObjectMemory.c ObjectMemoryTests.c vm_tests.c -o ast_tests
