#include <stdio.h>
#include "RealWordMemory.h"
#include "AllocationTests.h"
#include "FreeListTests.h"
#include "ObjectMemoryTests.h"
#include "RealWordMemoryTests.h"
#include "RefCountingTests.h"
#include "PrimitiveMethodTests.h"
#include "InterpreterMemoryTests.h"
#include "CompiledMethodTests.h"
#include "ContextTests.h"
#include "ClassTests.h"
#include "tests.h"

int main(int argc, const char *argv[]) {
  struct TestResult result;
  Bool hasMemory = NO;

  hasMemory = RealWordMemory_new();
  if (!hasMemory) {
    fprintf(stderr, "Unable to allocate heap space for the VM\n");
    return 1;
  }

  result.ran = 0;
  result.passed = 0;
  result.failed = 0;
  
  AllocationTests(&result);
  FreeListTests(&result);
  ObjectMemoryTests(&result);
  RealWordMemoryTests(&result);
  RefCountingTests(&result);
  PrimitiveMethodTests(&result);
  InterpreterMemoryTests(&result);
  CompiledMethodTests(&result);
  ContextTests(&result);
  ClassTests(&result);
  
  RealWordMemory_delete();

  printf("Tests completed.\n");
  printf("%d tests ran.\n", result.ran);
  printf("%d tests passed.\n", result.passed);
  printf("%d tests failed.\n", result.failed);
  
  return (result.failed != 0);
}
