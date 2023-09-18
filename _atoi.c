#include "shell.h"

/**
 *  * Check if the shell is in interactive mode.
 *   *
 *    * @param info: A pointer to a structure containing shell information.
 *     * @return 1 if the shell is in interactive mode, 0 otherwise.
 *      */
int isInteractive(info_t *info) {
	    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *  * Check if a character is a delimiter.
 *   *
 *    * @param c: The character to check.
 *     * @param delim: The delimiter string.
 *      * @return 1 if the character is a delimiter, 0 if not.
 *       */
int isDelimiter(char c, char *delim) {
	    while (*delim) {
		            if (*delim++ == c) {
				                return 1;
						        }
			        }
	        return 0;
}

/**
 *  * Check if a character is alphabetic.
 *   *
 *    * @param c: The character to check.
 *     * @return 1 if the character is alphabetic, 0 if not.
 *      */
int isAlphabetic(int c) {
	    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		            return 1;
			        } else {
					        return 0;
						    }
}

/**
 *  * Convert a string to an integer.
 *   *
 *    * @param s: The string to be converted.
 *     * @return 0 if there are no numbers in the string; otherwise, return the converted number.
 *      */
int stringToInteger(char *s) {
	    int i, sign = 1, flag = 0, output;
	        unsigned int result = 0;

		    for (i = 0; s[i] != '\0' && flag != 2; i++) {
			            if (s[i] == '-') {
					                sign *= -1;
							        }

				            if (s[i] >= '0' && s[i] <= '9') {
						                flag = 1;
								            result *= 10;
									                result += (s[i] - '0');
											        } else if (flag == 1) {
													            flag = 2;
														            }
					        }

		        if (sign == -1) {
				        output = -result;
					    } else {
						            output = result;
							        }

			    return output;
}

