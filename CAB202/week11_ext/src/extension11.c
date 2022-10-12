/***
 * Ex E11.0
 * 
 * Your task is to write code which handles a sequence of input characters
 * from the UART interface, and respond with the output specified below.
 * It is strongly recommended that you design a state machine to complete
 * this task, and practice drawing a state machine diagram before you
 * begin coding.
 * 
 * On receipt of the character sequence: 
 *   "foo" your programme should print '0' to the UART interface.
 *   "bar" your programme should print '1' to the UART interface.
 *   "foobar" your program should not print either '0' nor '1' as
 *   specified above, but should instead print a linefeed ('\n') 
 *   character.
 * 
 * Your solution should use a baud rate of 9600, and 8N1 frame format.
 * Your solution MUST NOT use qutyio.o or qutyserial.o.
 * 
 * Examples:
 * 
 *   Input:  
 *     ...foo.bar.foo.barfoobarfood
 *   Output: 
 *     0101
 *     0
 * 
 *   Input:
 *     barsfoosbarforbarfoobarrforfoobarfoobarfood
 *   Output:
 *     1011
 *     
 *     
 *     0
 */

int main(void) {


} // end main()