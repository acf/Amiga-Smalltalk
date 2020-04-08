#ifndef AMIGA_SMALLTALK_INTERPRETER_H
#define AMIGA_SMALLTALK_INTERPRETER_H

#include "Types.h"

#include "Interpreter_Constants.h"

/**
 * This register indicates whether a primitive method succeeded.
 * @note if the interpreter were written in Smalltalk, it would be possible to tell that failure
 *       has been returned from a method rather than a real value. But it isn't, and because most
 *       methods return object pointers (which are 16-bit words) or integers (same), there's no
 *       sentinel value that can be used. Additionally, we don't want to use longjmp() or a
 *       similar fake exception mechanism, because we need Smalltalk, not C, to recover from
 *       primitive method failures. We could use an out error parameter, but that would have a pervasive
 *       impact on the signatures of routines across the system. Therefore the official, supported way in
 *       this Smalltalk to test whether a primitive method failed is to check the value of the success
 *       register on return. If it's NO, then you shouldn't rely on the returned value.
 */
extern Bool success;

/**
 * Set the success register.
 * @note Actually ANDs the existing and new value, so if you previously failed, you will never un-fail.
 */
void Interpreter_success_(Bool successValue);

/**
 * Retrieve the success register.
 */
Bool Interpreter_success(void);

/**
 * Get ready to enter a primitive method.
 */
void Interpreter_initPrimitive(void);

/**
 * Indicate that execution of a primitive method failed.
 */
void Interpreter_primitiveFail(void);

/**
 * Convert the supplied integer into a SmallInteger object and store it in the object's field.
 * Fails if the integer cannot be stored in a SmallInteger (i.e. is higher magnitude than ±2^14)
 */
void Interpreter_storeInteger_ofObject_withValue(Word fieldIndex, ObjectPointer objectPointer, Word integerValue);

/**
 * Convert the SmallInteger object in the object's field to an integer value and return it.
 * Fails if the object pointer retrieved isn't an immediate integer.
 */
Word Interpreter_fetchInteger_ofObject(Word fieldIndex, ObjectPointer objectPointer);

/**
 * Transfer ownership of a collection of pointers between objects, setting the source fields to nil.
 */
void Interpreter_transfer_fromIndex_ofObject_toIndex_ofObject(
  Word count,
  Word firstFrom,
  ObjectPointer fromOop,
  Word firstTo,
  ObjectPointer toOop
);

/**
 * Extract a bit field from an integer value (not a pointer to an immediate integer, or other integer object).
 * The bits in a word are numbered 0 (most significant) to 15 (least significant), consistent with p575.
 */
Word Interpreter_extractBits_to_of(Word firstBitIndex, Word lastBitIndex, Word anInteger);

/**
 * Extract bits 0-7 of an integer word.
 */
Byte Interpreter_highByteOf(Word anInteger);

/**
 * Extract bits 8-15 of an integer word.
 */
Byte Interpreter_lowByteOf(Word anInteger);

/**
 * Find the header of a CompiledMethod. This is a SmallInteger used as a bitfield to describe the method.
 */
ObjectPointer Interpreter_headerOf(ObjectPointer methodPointer);

/**
 * Find the object literal at a given index in this CompiledMethod's literal frame.
 */
ObjectPointer Interpreter_literal_ofMethod(Word offset, ObjectPointer methodPointer);

/**
 * Extract the count of temporary object pointers from the CompiledMethod header.
 */
Byte Interpreter_temporaryCountOf(ObjectPointer methodPointer);

/**
 * Report whether a CompiledMethod needs a large method context.
 */
Bool Interpreter_largeContextFlagOf(ObjectPointer methodPointer);

/**
 * Extract the size of this CompiledMethod's literal frame.
 */
Byte Interpreter_literalCountOf(ObjectPointer methodPointer);

/**
 * Extract the size of a CompiledMethod's literal frame from an immediate integer representing its header.
 */
Byte Interpreter_literalCountOfHeader(ObjectPointer headerPointer);

/**
 * Extract the flag value of a CompiledMethod (see the discussion in Interpreter_Constants.h).
 * @see struct CompiledMethodHeader
 */
Byte Interpreter_flagValueOf(ObjectPointer methodPointer);

/**
 * Extract the field index of the ivar to return from a primitive CompiledMethod.
 * @note this value only makes sense if the CompiledMethod represents a primitive method that returns an
 *       instance variable from the receiver, i.e. if the CompiledMethod's flagValue is 6.
 */
Byte Interpreter_fieldIndexOf(ObjectPointer methodPointer);

/**
 * Read the header extension from a CompiledMethod that has one.
 * @note this value only makes sense when the CompiledMethod's flagValue is 7.
 */
ObjectPointer Interpreter_headerExtensionOf(ObjectPointer methodPointer);

/**
 * Return the number of arguments required by the CompiledMethod.
 */
Byte Interpreter_argumentCountOf(ObjectPointer methodPointer);

#endif
