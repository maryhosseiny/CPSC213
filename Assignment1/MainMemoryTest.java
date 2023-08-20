package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertFalse;

class MainMemoryTest {
    public MainMemory memory;
    
    @BeforeEach
    void setUp() {
        memory = new MainMemory(0);
        assertEquals(memory.length(), 0);
    }

    @Test
    void isAccessAlignedTest() {
        assertTrue(memory.isAccessAligned(8,4));    // aligned addr and correct length
        assertFalse(memory.isAccessAligned(11,4));  // incorrect addr for the selected length (smaller)
        assertFalse(memory.isAccessAligned(3,4));   // incorrect addr for the selected legnth (bigger)
        assertFalse(memory.isAccessAligned(8,7));   // incorrect length for the selected addr
        assertFalse(memory.isAccessAligned(9,7));   // incorrect length and addr
    }

    @Test
    void bytesToInteger() {
        // generating 0
        assertEquals(0, memory.bytesToInteger(((byte) 0x00),((byte) 0x00),((byte) 0x00),((byte) 0x00)));
        // generating the smallest positive value
        assertEquals(1, memory.bytesToInteger(((byte) 0x00),((byte) 0x00),((byte) 0x00),((byte) 0x01)));
        // generating small positive number
        assertEquals(128, memory.bytesToInteger(((byte) 0x00),((byte) 0x00),((byte) 0x00),((byte) 0x80)));
        // generating a number with the last byte as FF
        assertEquals(255, memory.bytesToInteger(((byte) 0x00),((byte) 0x00),((byte) 0x00),((byte) 0xFF)));
        // generating a large positive value
        assertEquals(16909060, memory.bytesToInteger(((byte) 0x01),((byte) 0x02),((byte) 0x03),((byte) 0x04)));
        // generating the largest negative value
        assertEquals(-1, memory.bytesToInteger(((byte) 0xFF),((byte) 0xFF),((byte) 0xFF),((byte) 0xFF)));
        // generating largest integer computable
        assertEquals(Integer.MAX_VALUE, memory.bytesToInteger(((byte) 0x7F),((byte) 0xFF),((byte) 0xFF),((byte) 0xFF)));
        // Testing to generate a smallest integer computable
        assertEquals(Integer.MIN_VALUE, memory.bytesToInteger(((byte) 0x80),((byte) 0x00),((byte) 0x00),((byte) 0x00)));
    }

    @Test
    void integerToBytes() {
        // generating 0
        assertEquals(((byte) 0x00),(memory.integerToBytes(0))[0]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(0))[1]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(0))[2]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(0))[3]);
        // generating 128
        assertEquals(((byte) 0x00),(memory.integerToBytes(128))[0]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(128))[1]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(128))[2]);
        assertEquals(((byte) 0x80),(memory.integerToBytes(128))[3]);
        // generating 255
        assertEquals(((byte) 0x00),(memory.integerToBytes(255))[0]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(255))[1]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(255))[2]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(255))[3]);
        // generating the largest computable value of integers
        assertEquals(((byte) 0x7F),(memory.integerToBytes(Integer.MAX_VALUE))[0]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(Integer.MAX_VALUE))[1]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(Integer.MAX_VALUE))[2]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(Integer.MAX_VALUE))[3]);
        // generating the smallest computable value of integers
        assertEquals(((byte) 0x80),(memory.integerToBytes(Integer.MIN_VALUE))[0]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(Integer.MIN_VALUE))[1]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(Integer.MIN_VALUE))[2]);
        assertEquals(((byte) 0x00),(memory.integerToBytes(Integer.MIN_VALUE))[3]);
        // generating -1 
        assertEquals(((byte) 0xFF),(memory.integerToBytes(-1))[0]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(-1))[1]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(-1))[2]);
        assertEquals(((byte) 0xFF),(memory.integerToBytes(-1))[3]);
    }

    @Test
    void set() {
        MainMemory newMemory = new MainMemory(128);
        // valid case: small byte size 
        try {
            newMemory.set(10, new byte[1]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown");
        }

        // valid case: address and value are valid
        try {
            newMemory.set(10, new byte[4]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown");
        }

        // invalid case: invalid address and valid value
        try {
            newMemory.set(-10, new byte[4]);
            fail("violating (address < 0) clause");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }

        // invalid case: memory size is bigger than (address + value)
        try {
            newMemory.set(10, new byte[180]);
            fail("violating ((address + value.length) > length())");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }

        // valid case: large array of bytes bigger than memory.length()
        try {
            newMemory.set(10, new byte[119]);
            fail("violating ((address + value.length) > length()) clause");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }

        // valid case: large array of bytes not bigger than memory.length()
        try {
            newMemory.set(10, new byte[118]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown");
        }
    }


    @Test
    void get() {
        MainMemory newMemory = new MainMemory(128);

        // valid case: small byte size 
        try {
            byte[] result = newMemory.get(10, 1);
            assertEquals(result.length, 1);
            assertFalse(result.length == 2); 
            assertFalse(result.length == 0);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown");
        }

        // valid case: address and value are correct
        try {
            byte[] result = newMemory.get(10, 4);
            assertEquals(result.length, 4);
            assertFalse(result.length == 5); 
            assertFalse(result.length == 3);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown"); 
        }

        // invalid case: invalid address and valid value
        try {
            newMemory.get(-10, 4);
            fail("violating (address < 0) clause");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }

        // invalid case: memory size is bigger than (address + value)
        try {
            newMemory.get(10, 180);
            fail("violating ((address + value.length) > length()) clause");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }

        // valid case: large array of bytes not bigger than memory.length())
        try {
            byte[] result = newMemory.get(10, 118);
            assertEquals(result.length, 118);
            assertFalse(result.length == 119);
            assertFalse(result.length == 117);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("unexpected behaviour if exception is thrown");
        }

        // case with a array of bytes bigger than memory.length())
        try {
            newMemory.get(10, 119);
            fail("violating ((address + value.length) > length())");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            //expected behaviour
        }
    }

}
