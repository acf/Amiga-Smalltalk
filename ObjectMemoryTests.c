#include "ObjectMemoryTests.h"
#include "ObjectMemory.h"
#include "RealWordMemory.h"

short test_NonIntegerObjectIsNotIntegerObject() {
  short result = ObjectMemory_isIntegerObject(0);
  return !result;
}

short test_IntegerObjectIsIntegerObject() {
  short result = ObjectMemory_isIntegerObject(1);
  return result;
}

short test_ObjectTableLookupFindsWordInRealWordMemory() {
  ObjectPointer objectPointer = 0x2468;
  short value = 0xbeef, result = 0;
  RealWordMemory_segment_word_put(ObjectTableSegment,
    ObjectTableStart + objectPointer,
    value);
  result = ObjectMemory_ot(objectPointer);
  return (result == value);
}

short test_ObjectTableStorageSetsWordInRealWordMemory() {
  ObjectPointer objectPointer = 0x1234;
  short value = 0xcafe, result = 0;
  ObjectMemory_ot_put(objectPointer, value);
  result = RealWordMemory_segment_word(ObjectTableSegment,
    ObjectTableStart + objectPointer);
  return (result == value);
}

short test_ObjectTableStorageRetrievesSpecificBitsInRealWordMemory() {
  ObjectPointer objectPointer = 0x369C;
  short value = 0xAAAA, firstBitIndex = 0, lastBitIndex = 3, result = 0, expected = 0xA;
  ObjectMemory_ot_put(objectPointer, value);
  result = ObjectMemory_ot_bits_to(objectPointer, firstBitIndex, lastBitIndex);
  return (result == expected);
}

short test_ObjectTableStorageSetsSpecificBitsInRealWordMemory() {
  ObjectPointer objectPointer = 0xfda0;
  short value = 0, firstBitIndex = 11, lastBitIndex = 14, setBits = 0xf, result = 0, expected = 0x1e;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_ot_bits_to_put(objectPointer, firstBitIndex, lastBitIndex, setBits);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

void ObjectMemoryTests(struct TestResult *tr) {
  RunTest(test_NonIntegerObjectIsNotIntegerObject);
  RunTest(test_IntegerObjectIsIntegerObject);
  RunTest(test_ObjectTableLookupFindsWordInRealWordMemory);
  RunTest(test_ObjectTableStorageSetsWordInRealWordMemory);
  RunTest(test_ObjectTableStorageRetrievesSpecificBitsInRealWordMemory);
  RunTest(test_ObjectTableStorageSetsSpecificBitsInRealWordMemory);
}
