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

short test_CountBitsInObjectStorageAreMostSignificantByteOfObjectHeader() {
  ObjectPointer objectPointer = 0x1234;
  short value = 0xbbcc, countBits = 0, expected = 0xbb;
  ObjectMemory_ot_put(objectPointer, value);
  countBits = ObjectMemory_countBitsOf(objectPointer);
  return (countBits == expected);
}

short test_CountBitsStoredInMostSignificantByteOfObjectHeader() {
  ObjectPointer objectPointer = 0xfffe;
  short value = 0x1122, countBits = 0x35, result = 0, expected = 0x3522;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_countBitsOf_put(objectPointer, countBits);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

short test_OddBitIsAtBitEightOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 1<<7, result = 0, expected = 1;
  ObjectMemory_ot_put(objectPointer, value);
  result = ObjectMemory_oddBitOf(objectPointer);
  return (result == expected);
}

short test_OddBitIsSetAtBitEightOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 0, bit = 1, result = 0, expected = 1<<7;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_oddBitOf_put(objectPointer, bit);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

short test_PointerBitIsAtBitNineOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 1<<6, result = 0, expected = 1;
  ObjectMemory_ot_put(objectPointer, value);
  result = ObjectMemory_pointerBitOf(objectPointer);
  return (result == expected);
}

short test_PointerBitIsSetAtBitNineOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 0, bit = 1, result = 0, expected = 1<<6;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_pointerBitOf_put(objectPointer, bit);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

short test_FreeBitIsAtBitTenOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 1<<5, result = 0, expected = 1;
  ObjectMemory_ot_put(objectPointer, value);
  result = ObjectMemory_freeBitOf(objectPointer);
  return (result == expected);
}

short test_FreeBitIsSetAtBitTenOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 0, bit = 1, result = 0, expected = 1<<5;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_freeBitOf_put(objectPointer, bit);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

short test_SegmentBitsAtLowestNybbleOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 0x000f, segment = 0, expected = 0xf;
  ObjectMemory_ot_put(objectPointer, value);
  segment = ObjectMemory_segmentBitsOf(objectPointer);
  return (segment == expected);
}

short test_SegmentBitsStoredInLowestNybbleOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short value = 0x0000, segment = 0xf, result = 0, expected = 0x000f;
  ObjectMemory_ot_put(objectPointer, value);
  ObjectMemory_segmentBitsOf_put(objectPointer, segment);
  result = ObjectMemory_ot(objectPointer);
  return (result == expected);
}

short test_LocationBitsAreInTheSecondWordOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short locationWord = objectPointer + 1, value = 0xcafe, result = 0;
  RealWordMemory_segment_word_put(ObjectTableSegment,
    ObjectTableStart + locationWord,
    value);
  result = ObjectMemory_locationBitsOf(objectPointer);
  return (result == value);
}

short test_LocationBitsStoredInSecondWordOfObjectHeader() {
  ObjectPointer objectPointer = 0x0;
  short locationWord = objectPointer + 1, value = 0xb33f, result = 0;
  ObjectMemory_locationBitsOf_put(objectPointer, value);
  result = RealWordMemory_segment_word(ObjectTableSegment,
    ObjectTableStart + objectPointer + 1);
  return (result == value);
}

short test_GrabbingHeapChunkOfObjectGetsWordDeeperIntoMemory() {
  ObjectPointer objectPointer = 0x1000;
  short segment = 1, location = 0x0f0f, offset = 4, value = 0x4321, result = 0;
  ObjectMemory_locationBitsOf_put(objectPointer, location);
  ObjectMemory_segmentBitsOf_put(objectPointer, segment);
  RealWordMemory_segment_word_put(segment,
    location + offset,
    value);
    
  result = ObjectMemory_heapChunkOf_word(objectPointer, offset);
  return (result == value);
}

short test_StoringHeapChunkOfObjectWritesWordDeeperIntoMemory() {
  ObjectPointer objectPointer = 0x100e;
  short segment = 3, location = 0xcccc, offset = 0xaa, value = 0x4321, result = 0;
  ObjectMemory_locationBitsOf_put(objectPointer, location);
  ObjectMemory_segmentBitsOf_put(objectPointer, segment);
  ObjectMemory_heapChunkOf_word_put(objectPointer, offset, value);

  result = RealWordMemory_segment_word(segment, location+offset);
  return(result == value);
}

short test_GetHeapChunkOfObjectMemoryByByte() {
  ObjectPointer objectPointer = 0x2222;
  short segment = 5, location = 0x0202, wordOffset = 0x40, wordValue = 0xfedc, byteOffset = (wordOffset * 2) + 1;
  char lowByte = 0, expected = 0xdc;
  ObjectMemory_locationBitsOf_put(objectPointer, location);
  ObjectMemory_segmentBitsOf_put(objectPointer, segment);
  ObjectMemory_heapChunkOf_word_put(objectPointer, wordOffset, wordValue);
  lowByte = ObjectMemory_heapChunkOf_byte(objectPointer, byteOffset);
  return (lowByte == expected);
}

short test_StoreHeapChunkOfObjectMemoryByByte() {
  ObjectPointer objectPointer = 0x3434;
  short segment = 2, location = 0x099a, wordOffset = 0x72, byteOffset = (wordOffset * 2), retrieved = 0;
  char byteValue = 0xb4;
  ObjectMemory_locationBitsOf_put(objectPointer, location);
  ObjectMemory_segmentBitsOf_put(objectPointer, segment);
  ObjectMemory_heapChunkOf_byte_put(objectPointer, byteOffset, byteValue);
  retrieved = ObjectMemory_heapChunkOf_word(objectPointer, wordOffset);
  return (retrieved == ((short)byteValue) << 8);
}

void ObjectMemoryTests(struct TestResult *tr) {
  RunTest(test_NonIntegerObjectIsNotIntegerObject);
  RunTest(test_IntegerObjectIsIntegerObject);
  RunTest(test_ObjectTableLookupFindsWordInRealWordMemory);
  RunTest(test_ObjectTableStorageSetsWordInRealWordMemory);
  RunTest(test_ObjectTableStorageRetrievesSpecificBitsInRealWordMemory);
  RunTest(test_ObjectTableStorageSetsSpecificBitsInRealWordMemory);
  RunTest(test_CountBitsInObjectStorageAreMostSignificantByteOfObjectHeader);
  RunTest(test_CountBitsStoredInMostSignificantByteOfObjectHeader);
  RunTest(test_OddBitIsAtBitEightOfObjectHeader);
  RunTest(test_OddBitIsSetAtBitEightOfObjectHeader);
  RunTest(test_PointerBitIsAtBitNineOfObjectHeader);
  RunTest(test_PointerBitIsSetAtBitNineOfObjectHeader);
  RunTest(test_FreeBitIsAtBitTenOfObjectHeader);
  RunTest(test_FreeBitIsSetAtBitTenOfObjectHeader);
  RunTest(test_SegmentBitsAtLowestNybbleOfObjectHeader);
  RunTest(test_SegmentBitsStoredInLowestNybbleOfObjectHeader);
  RunTest(test_LocationBitsAreInTheSecondWordOfObjectHeader);
  RunTest(test_LocationBitsStoredInSecondWordOfObjectHeader);
  RunTest(test_GrabbingHeapChunkOfObjectGetsWordDeeperIntoMemory);
  RunTest(test_StoringHeapChunkOfObjectWritesWordDeeperIntoMemory);
  RunTest(test_GetHeapChunkOfObjectMemoryByByte);
  RunTest(test_StoreHeapChunkOfObjectMemoryByByte);
}
