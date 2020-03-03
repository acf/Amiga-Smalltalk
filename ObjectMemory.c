#include "ObjectMemory.h"
#include "RealWordMemory.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void ObjectMemory_cantBeIntegerObject(ObjectPointer op) {
  if ((op & 0x0001) != 0) {
    fprintf(stderr, "Trying to use integer object %x", op);
  }
  assert((op & 0x0001) == 0);
}

Word ObjectMemory_isIntegerObject(Word objectPointer) {
  return (objectPointer & 0x0001);
}

Word ObjectMemory_ot(ObjectPointer objectPointer) {
  ObjectMemory_cantBeIntegerObject(objectPointer);
  return RealWordMemory_segment_word(ObjectTableSegment,
    ObjectTableStart + objectPointer);
}

void ObjectMemory_ot_put(ObjectPointer objectPointer, Word value) {
  RealWordMemory_segment_word_put(ObjectTableSegment,
    ObjectTableStart + objectPointer,
    value);
}

Word ObjectMemory_ot_bits_to(ObjectPointer objectPointer, Word firstBitIndex, Word lastBitIndex) {
  return RealWordMemory_segment_word_bits_to(ObjectTableSegment,
    ObjectTableStart + objectPointer,
    firstBitIndex,
    lastBitIndex);
}

void ObjectMemory_ot_bits_to_put(ObjectPointer objectPointer, Word firstBitIndex, Word lastBitIndex, Word value) {
  RealWordMemory_segment_word_bits_to_put(ObjectTableSegment,
    ObjectTableStart + objectPointer,
    firstBitIndex,
    lastBitIndex,
    value);
}
