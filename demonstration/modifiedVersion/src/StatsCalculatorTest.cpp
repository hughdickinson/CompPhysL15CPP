/// \file StatsCalculatorTest.cpp Testing for StatsCalculator class

// The <iostream> header is included to enable textual terminal output.
#include <iostream>

/* Include StatsCalculator.h to provide class definition of
 * StatsCalculator
 */
#include "StatsCalculator.h"

/** The main function is the entry point for the program. The program is designed
 * to be invoked with two command line arguments and will output an error message
 * if the incorrect number of command line arguments is not supplied.
 *
 * \param argc - The number of command line tokens including the executable name 
 * and command line arguments.
 *
 * \param argv - The \b first command line argument, available as argv[1] is expected to be the
 * path of an input file containing a white-space separated list of numeric values.
 * The \b second command line argument, available as argv[2] is expected to be the
 * path to which a file containing a statistical summary of the numeric values
 * provided by the input file.
 *
 * The program instantiates a StatsCalculator object and invokes its public methods
 * in order to:
 *
 * -# Open the input file, parse its contents and store the numeric values in an
 * internal std::vector<double>.
 * -# Print a statistical summary comprising the sum, mean and standard deviation
 * of the numeric values to the terminal.
 * -# Individually access each statistic and print their values to the terminal with
 * annotation.
 * -# Write a statistical summary comprising the sum, mean and standard deviation
 * of the numeric values to the user-specified output file.
 *
 * \return The program returns zero on success and 1 if an incorrect number of command line
 * arguments was provided.
 */
int main(int argc, char * argv[]){
    
    /* Verify that the program was invoked with TWO command line arguments.
     * Recall that argc enumerates all the command line tokens, including
     * the executable name itself.
     */
    if(argc == 3){
        // Instantiate a StatsCalculator object with identifier "statsCalculator"
        StatsCalculator statsCalculator;
        
        /* Call the readFile method provided by StatsCalculator, passing the 
         * FIRST command line argument stored in the character-array "argv[1]".
         *
         * This will attempt to read a sequence of whitespace-spearated numeric
         * values from a text file at the file-system path specified by "argv[1]".
         *
         * Technical Note: The readFile(...) method requires a reference to a 
         * std::string as its argument. C++ is able to implicitly convert 
         * "argv[1]" (which has type "char *" to the required type because 
         * std::string provides a constructor that accepts a "char *" as its 
         * single argument. This is known as a "Converting Constructor".
         */
        statsCalculator.readFile(argv[1]);
        
        /* Call the printStats() method provided by StatsCalculator. This 
         * outputs a formatted summary of the statistical properties of the 
         * numerical values that were extracted from the input file to the
         * terminal.
         */
        statsCalculator.printStats();
        
        /* Individually call the getter methods for each of the computable
         * statistics and output their values to the terminal.
         */
        std::cout << "getSum() => " << statsCalculator.getSum() << "\n"
        << "getMean() => " << statsCalculator.getMean() << "\n"
        << "getStandardDeviation() => " << statsCalculator.getStandardDeviation() << "\n"
        << std::endl;
        
        /* Call the writeStats() method provided by StatsCalculator. This
         * outputs a formatted summary of the statistical properties of the
         * numerical values that were extracted FROM the input file TO the
         * output file specified by the SECOND command line argument stored 
         * in the character-array "argv[1]".
         */
        statsCalculator.writeStats(argv[2]);
        
        // return 0 on success
        return 0;
    }
    else{ // An invalid number of arguments was provided.
        
        /* Output an informative message explaining the required program
         * invocation syntax.
         */
        std::cout << "Required Syntax:\n\n"
        << "./statsCalculator inputFile outputFile\n\n"
        << "Argument Descriptions:\n\n"
        << "inputFile - The path of a text file containing "
        << "whitespace-separated numeric values.\n\n"
        << "outputFile - A path to which an output text file "
        << "containing a statistical summary of the numeric "
        << "values should be written."
        << std::endl;
        
        /* There was a problem with execution, so return a 
         * non-zero integer value.
         */
        return 1;
    }
    /* The previous if-else clause is exhaustive. Program control should never
     * reach this point.
     */
}
