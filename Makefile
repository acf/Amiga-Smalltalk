check: ast_tests
	./ast_tests

.PHONY: check

SOURCE_FILES = ObjectMemory.c ObjectMemory_Storage.c ObjectMemory_FreeList.c ObjectMemory_Allocation.c ObjectMemory_RefCounting.c ObjectMemory_MarkingCollector.c RealWordMemory.c Interpreter.c
HEADER_FILES = ObjectMemory.h ObjectMemory_Constants.h ObjectMemory_Storage.h ObjectMemory_FreeList.h ObjectMemory_Allocation.h ObjectMemory_RefCounting.h ObjectMemory_MarkingCollector.h RealWordMemory.h Types.h Interpreter.h Interpreter_Constants.h

TEST_SOURCES = test_main.c FreeListTests.c ObjectMemoryTests.c RealWordMemoryTests.c AllocationTests.c RefCountingTests.c PrimitiveMethodTests.c InterpreterMemoryTests.c CompiledMethodTests.c ContextTests.c
TEST_HEADERS = tests.h FreeListTests.h ObjectMemoryTests.h RealWordMemoryTests.h AllocationTests.h RefCountingTests.h PrimitiveMethodTests.h InterpreterMemoryTests.h CompiledMethodTests.h ContextTests.h

ast_tests: $(SOURCE_FILES) $(HEADER_FILES) $(TEST_SOURCES) $(TEST_HEADERS)
	gcc -ggdb $(SOURCE_FILES) $(TEST_SOURCES) -o ast_tests
