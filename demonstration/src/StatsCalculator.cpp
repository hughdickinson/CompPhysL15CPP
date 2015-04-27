// IMPLEMENTATION file for StatsCalculator class

// STL HEADER FILES

// The <cmath> header is included to provide the std::sqrt(...) function.
#include <cmath>
// The <fstream> header is included to enable input from and output to files.
#include <fstream>
// The <iostream> header is included to enable textual terminal output.
#include <iostream>

// LOCAL HEADER FILES

/* The "StatsCalculator.h" header is included to provide a definition of the
 * StatsCalculator class.
 */
#include "StatsCalculator.h"

// PUBLIC METHODS OF STATSCALCULATOR

/** Private method that actually computes the sum of the stored numeric
 * values.
 *
 * \return The computed sum is returned as a double-precision value.
 */
double StatsCalculator::computeSum(){
    
    // If any numeric values were successfully parsed from the input file...
    if(numericValues.size() > 0){
        
        /* Declare and zero-initialize a double precision variable with
         * identifier "sum" store the computed sum
         */
        double sum(0.0);
        
        /* Use the range-based for-loop syntax to iterate over all elements
         * of the "numericValues" member datum.
         *
         * The value of the current element of "numericValues" will be
         * accessible within the for-loop body using the identifier
         * "numericValue".
         */
        for(double numericValue : numericValues){
            /* Update the value of "sum" by adding the value of the current
             * element of "numericValues"
             */
            sum += numericValue;
        }
        // return the computed sum of all elements of "numericValues"
        return sum;
    }
    else{ // No numeric values were successfully parsed from the input file
        return 0.0;
    }
    
}

/** Private method that actually computes the mean of the stored numeric
 * values.
 *
 * \return The computed mean is returned as a double-precision value.
 *
 * The mean of a sequence of numbers is equal to their sum divided
 * by their multiplicity.
 *
 * \note Computation of the required sum can be delegated
 * to the computeSum() method of StatsCalculator, while the
 * number of elements in the sequence is provided by the size() method
 * of the std::vector<double>-type member datum "numericValues".
 */
double StatsCalculator::computeMean(){
    
    // If any numeric values were successfully parsed from the input file...
    if(numericValues.size() > 0){
        
        // compute and return the mean of the elements of "numericValues"
        return computeSum()/numericValues.size();
    }
    else{ // No numeric values were successfully parsed from the input file
        return 0.0;
    }
}

/** Private method that actually computes the standard deviation of the
 * stored numeric values.
 *
 * \return The computed standard deviation is returned as a double-precision value.
 *
 * The standard deviation of a sequence of numbers is can be computed
 * as the square root of the difference between the mean of the squares
 * of the numbers and the square of the mean of the numbers.
 *
 * \f[ \sigma = \sqrt{\langle X^{2} \rangle - \langle X \rangle^{2}} \f]
 */
double StatsCalculator::computeStandardDeviation(){
    
    // If any numeric values were successfully parsed from the input file...
    if(numericValues.size() > 0){
        
        /* Declare and zero-initialize a double precision variable with
         * identifier "meanOfSquaredValues" that will ultimately contain
         * the mean of the squares of the elements of the "numericValues"
         * member datum.
         */
        double meanOfSquaredValues(0.0);
        
        /* Use the range-based for-loop syntax to iterate over all elements
         * of the "numericValues" member datum.
         *
         * The value of the current element of "numericValues" will be
         * accessible within the for-loop body using the identifier
         * "numericValue".
         */
        for(double numericValue : numericValues){
            /* Update the value of "meanOfSquaredValues" by adding the square
             * of the value of the current element of "numericValues"
             */
            meanOfSquaredValues += numericValue*numericValue;
        }
        
        /* The current value of "meanOfSquaredValues" corresponds to the SUM
         * of the squares of the elements of "numericValues". The required mean
         * can be obtained by dividing by the number of elements comprising
         * numericValues. This number is returned by the  size() method
         * of the std::vector<double>-type member datum "numericValues".
         */
        meanOfSquaredValues /= numericValues.size();
        
        /* Compute and return the required standard deviation. The square
         * of the mean of the elements of "numericValues" is computed
         * by delegating computation of the mean to getMean() and squaring
         * the result.
         *
         * Technical note: It would be more efficient to call getMean() once,
         * then store and square the result. In reality, almost all modern
         * optimizing compilers will recognize this and produce equivalent
         * machine code from the subsequent statement.
         *
         * The STL function std::sqrt provided by the <cmath> header file is
         * used to compute the square root.
         */
        return std::sqrt(meanOfSquaredValues - getMean()*getMean());
    }
    else{ // No numeric values were successfully parsed from the input file
        return 0.0;
    }
}


// PUBLIC METHODS OF STATSCALCULATOR

/** Default constructor for the StatsCalculator class, which is not
 * required to perform any operations.
 *
 * \note Technically an identical definition would be provided by the
 * C++ compiler if its delcaration were also omitted from the class
 * definition in the StatsCalculator.h header file.
 *
 * \note The explicit declaration and (no-operation) definition are
 * provided for clarity.
 */
StatsCalculator::StatsCalculator(){
    // No initialization operations are required.
}

/** Destructor for the StatsCalculator class, which is not
 * required to perform any operations.
 *
 * \note Technically an identical definition would be provided by the
 * C++ compiler if its delcaration were also omitted from the class
 * definition in the StatsCalculator.h header file.
 *
 * \note The explicit declaration and (no-operation) definition are
 * provided for clarity.
 */
StatsCalculator::~StatsCalculator(){
    // No deallocation operations are required.
}

/** Public method returns the sum of the internally stored numeric values.
 *
 * \note The method delegates the computation of the required sum to the private
 * computeSum() method.
 *
 * \return The computed sum is returned as a double-precision value.
 */
double StatsCalculator::getSum(){
    return computeSum();
}


/** Public method returns the mean of the internally stored numeric values.
 *
 * \note The method delegates the computation of the required mean to the private
 * computeMean() method.
 *
 * \return The computed mean is returned as a double-precision value.
 */
double StatsCalculator::getMean(){
    return computeMean();
}


/** Public method returns the standard deviation of the internally stored
 * numeric values.
 *
 * \note The method delegates the computation of the required standard deviation
 * to the private computeSum() method.
 *
 * \return The computed standard deviation is returned as a double-precision value.
 */
double StatsCalculator::getStandardDeviation(){
    return computeStandardDeviation();
}


/**  Public method that accepts a appends a new double precision value to
 * the "numericValues" member datum.
 *
 * \param value - A double precision value to append to the "numericValues" member
 * datum.
 */
void StatsCalculator::appendValue(double value){
    numericValues.push_back(value);
}

/** Public method that reads a list of whitespace-separated numeric
 * values from a text file. It appends those values to the "numericValues"
 * member datum.
 */
void StatsCalculator::readFile(const std::string & infileName){
    
    // Print an informative message to inform the caller of progress.
    std::cout << "Reading data from:\n\n" << infileName << std::endl;
    
    /* Declare and zero-initialize a double precision variable with
     * identifier "numericValue" to provide temporary storage for
     * numeric values that are parsed from the input text file.
     */
    double numericValue(0.0);
    
    /* Instantiate a std::ifstream object that will be appropriately
     * configured to read data from a file at the path specified by
     * the method argument "infileName".
     *
     * Note that the constructor requires a C-String as its argument
     * and the c_str() method of std::string must be called to extract
     * the required type from the std::string instance.
     */
    std::ifstream inputFile(infileName.c_str());
    
    /* The following if clause ensures that the input file was
     * successfully opened AND that the file is in a good state
     * for reading. The former criterion is established if the
     * to the is_open() method provided by std::ifstream returns
     * true. The latter criterion is established if the good()
     * method provided by std::ifstream returns true.
     *
     * Technical Note: In C++ the logical and "&&" operator uses
     * "short-circuit" semantics. Since both operands MUST evaluate
     * to true in order for the expression to be true, it is possible
     * to determine the expression result by examining only one
     * operand IF that operand evaluates to false. By convention
     * C++ examines the left-hand operand first and does not evaluate
     * the right-hand operand if the left-hand operand is false.
     * This means that if the file is NOT open, then no attempt will
     * be made to assess its readability state.
     */
    if(inputFile.is_open() && inputFile.good()){
        /* Begin a while loop that will iterate until the end of the
         * file is reached (inputFile.eof() == true) or the file
         * becomes unreadable (inputFile.good() == false). Note the
         * use of the "!" operator to invert the return value of
         * inputFile.eof().
         */
        while(!inputFile.eof() && inputFile.good()){
            /* The stream input operator (">>") extracts a whitespace-
             * separated token (character sequence) from the input file
             * and attempts to interpret the sequence as a double
             * precision value. If successful, it assigns the interpretted
             * value to the "numericValue" variable
             */
            inputFile >> numericValue;
            /* The push_back() method provided by std::vector<double> is
             * invoked to append the extracted numeric value to the end of
             * the numericValues member datum.
             */
            numericValues.push_back(numericValue);
        }
        /* Explicitly close the input file, freeing any resources it acquired
         * when it was constructed or during its operation.
         */
        inputFile.close();
    }
    
    // If any numeric values were successfully parsed from the input file...
    if(numericValues.size() > 0){
        /* Print a summary of the extracted data to the terminal in the format
         * "Data = [ value1, value2, ..., valueN ]".
         */
        
        // Output some preamble
        std::cout << "Data = [ ";
        // Loop over all but the last element of the "numericValues" member datum
        for(std::vector<double>::iterator numValIt = numericValues.begin();
            numValIt != --numericValues.end();
            ++numValIt){
            /* Output the value of the current element of "numericValues", followed
             * by a comma.
             */
            std::cout << *numValIt << ", ";
        }
        /* Output the value of the final element of "numericValues", followed
         * by a square bracket and two newlines. Flush the output buffer.
         */
        std::cout << *(--numericValues.end())
        << " ]\n" << std::endl;
    }
}

/** Public method that prints a summary of the statistical properties that this
 * class computes to the terminal.
 */
void StatsCalculator::printStats(){
    /* Output a multiline formatted message to the terminal. The first line
     * is a simple explanatory header. The next three lines output annotated
     * values of the statistical quantities that are computed by the class
     * using the format: "Statistic_Name = Statistic_Value"
     *
     * The required statistical values are obtained using the public getter
     * methods: getSum(), getMean() and getStandardDeviation()
     */
    std::cout << "Simple statistical analysis of numeric data:\n\n"
    << "Sum =  " << getSum() << "\n"
    << "Mean = " << getMean() << "\n"
    << "Standard Deviation = " << getStandardDeviation()
    << "\n" << std::endl;
}

/** Public method that writes a summary of the statistical properties that this
 * class computes to a caller-specified output file.
 */
void StatsCalculator::writeStats(const std::string & outfileName){
    /* Instantiate a std::ofstream object that will be appropriately
     * configured to write data to a file at the path specified by
     * the method argument "outfileName".
     *
     * If the file does not exist it will be created. If the file
     * does exist it will be overwritten.
     *
     * Note that the constructor requires a C-String as its argument
     * and the c_str() method of std::string must be called to extract
     * the required type from the std::string instance.
     */
    std::ofstream outputFile(outfileName.c_str());
    
    /* The following if clause ensures that the input file was
     * successfully opened AND that the file is in a good state
     * for reading. The former criterion is established if the
     * to the is_open() method provided by std::ifstream returns
     * true. The latter criterion is established if the good()
     * method provided by std::ifstream returns true.
     */
    if(outputFile.is_open() && outputFile.good()){
        /* Output a multiline formatted message to the sucessfully
         * opened output file.
         *
         * The first line is a simple explanatory header. The next three lines
         * output annotated values of the statistical quantities that are computed
         * by the class using the format: "Statistic_Name = Statistic_Value"
         *
         * The required statistical values are obtained using the public getter
         * methods: getSum(), getMean() and getStandardDeviation()
         */
        outputFile << "Simple statistical analysis of numeric data:\n\n"
        << "Sum =  " << getSum() << "\n"
        << "Mean = " << getMean() << "\n"
        << "Standard Deviation = " << getStandardDeviation()
        << "\n" << std::endl;
        
        /* Explicitly close the input file, freeing any resources it acquired
         * when it was constructed or during its operation.
         *
         * This also ensures that the output buffer has been flushed and all
         * data has been written to the output file.
         */
        outputFile.close();
    }
    /* Output an informative message to inform the caller of successful
     * operation of the method.
     */
    std::cout << "A statistical summary has been saved to:\n\n"
    << outfileName
    << std::endl;
}
