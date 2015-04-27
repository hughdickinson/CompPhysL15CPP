// Define the STATSCALCULATOR_H macro to act as an include guard
#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

/* This header file may be parsed by a C compiler. If this happens, any 
 * C++-only language constructs (e.g. class definitions or references to 
 * std::string or std::vector) in the code will cause the compilation to 
 * fail.
 *
 * To prevent a C compiler from attempting to parse C++ code, wrap that code
 * in a PREPROCESSOR CONDITIONAL block that depends upon the "__cplusplus"
 * macro being defined.
 *
 * This will only be the case if a C++ compiler is considering the code.
 */
#ifdef __cplusplus
    
// Include the <vector> header to provide the STL std::vector type.
#include <vector>

// Include the <string> header to provide the STL std::vector type.
#include <string>

/** \class StatsCalculator
 * The StatsCalculator class reads a list of whitespace-separated numeric
 * values from a text file. It stores those values internally and supplies
 * methods to compute and return several statistical properties of those
 * numbers.
 *
 * It provides a method that prints a summary of the statistical properties
 * of its internally stored numbers to the terminal and another method that
 * writes a similar summary to a textual output file.
 */
class StatsCalculator {
    
    /** \brief An STL vector of double precision values to store parsed numeric
     * values.
     */
    std::vector<double> numericValues;
    
    /** \brief Private method that actually computes the sum of the stored numeric
     * values.
     */
    double computeSum();
    
    /** \brief Private method that actually computes the mean of the stored numeric
     * values.
     */
    double computeMean();
    
    /** \brief Private method that actually computes the standard deviation of the
     * stored numeric values.
     */
    double computeStandardDeviation();
    
public:
    
    /** \brief Default constructor.
     */
    StatsCalculator();
    
    /** \brief Destructor.
     */
    ~StatsCalculator();
    
    /** \brief Public method returns the sum of the internally stored numeric values.
     */
    double getSum();
    
    /** \brief Public method returns the mean of the internally stored numeric values.
     */
    double getMean();
    
    /** \brief Public method returns the standard deviation of the internally stored
     * numeric values.
     */
    double getStandardDeviation();
    
    /** \brief Public method that accepts a appends a new double precision value to  
     * the "numericValues" member datum.
     *
     * \param value - A double precision value to append to the "numericValues" member 
     * datum.
     */
    void appendValue(double value);
    
    /** \brief Public method that reads a list of whitespace-separated numeric
     * values from a text file. It appends those values to the "numericValues"
     * member datum.
     *
     * \param infileName - A string specifying to the path of a text file containing
     *    a whitespace-separated list of numeric values.
     */
    void readFile(const std::string & infileName);
    
    /** \brief Public method that prints a summary of the statistical properties that this
     * class computes to the terminal.
     */
    void printStats();
    
    /** \brief Public method that writes a summary of the statistical properties that this
     * class computes to a caller-specified output file.
     *
     * \param outfileName - A string specifying to the path for a text file to which
     * the statistics summary should be written.
     */
    void writeStats(const std::string & outfileName);
    
};

/* This is the end of the first block of C++-only code, so end the __cplusplus conditional block.
 */
#endif // __cplusplus was defined

/* Now declare some WAPPER FUNCTIONS that provide access for C compilers to
 * the functionality provided by StatsCalculator.
 * 
 * The IMPLEMENTATIONS of these functions will reference C++-only language 
 * constructs that must be compiled using a C++ compiler. However the default
 * NAME MANGLING behaviour of the C++ compiler must be suppressed. This is 
 * done by specifying that the functions should be declared with C-STYLE
 * LINKAGE. This is achieved by enclosing the function definititions within a
 * code block that is prpended with the keyword "extern" and the string literal
 * "C".
 *
 * The final complication is that C compilers cannot parse the 'extern "C"' token
 * pair, so a PREPROCESSOR CONDITIONAL that depends on the __cplusplus macro
 * is required. Another conditional block is also required to hide the closing 
 * brace of the code block from C compilers.
 */
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus was defined
    
    /** \brief C API function that instantiates a StatsCalculator object and returns an
     * integer "handle" to the user that can be used to reference the object.
     *
     * \return An integer "handle" that uniquely refers to the instantiated 
     * StatsCalculator object.
     */
    int statsCalcCreate();
    
    /** \brief Destroy a previously instantiated StatsCalculator object.
     * 
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be destroyed.
     */
    void statsCalcDestroy(int handle);
    
    /** \brief Expose the functionality of StatsCalculator::appendValue() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to parse the file.
     * \param value - A double precision value to append to the "numericValues" 
     * member datum of the StatsCalculator instance to which handle refers.
     */
    void statsCalcAppendValue(int handle, double value);
    
    /** \brief Expose the functionality of StatsCalculator::readFile() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to parse the file.
     * \param fileName - A C-string specifying the path of the file to be
     * opened and parsed.
     */
     void statsCalcReadFile(int handle, const char * fileName);
    
    /** \brief Expose the functionality of StatsCalculator::writeStats() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to write its computed statistics to a file.
     * \param fileName - A C-string specifying the path of the file to be
     * written.
     */
    void statsCalcWriteStats(int handle, const char * fileName);
    
    /** \brief Expose the functionality of StatsCalculator::getSum() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to return the sum of its stored numeric data.
     *
     * \return The sum of the numeric data stored by the StatsCalculator 
     * instance to which handle refers.
     */
    double statsCalcGetSum(int handle);
    
    /** \brief Expose the functionality of StatsCalculator::getMean() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to return the mean of its stored numeric data.
     *
     * \return The mean of the numeric data stored by the StatsCalculator
     * instance to which handle refers.
     */
    double statsCalcGetMean(int handle);
    
    /** \brief Expose the functionality of StatsCalculator::getStdDev() in the
     * C API.
     *
     * \param handle - an integer that was returned by statsCalcCreate() and
     * uniquely references the instance of StatsCalculator that should
     * be induced to return the mean of its stored numeric data.
     *
     * \return The standard deviation of the numeric data stored by the 
     * StatsCalculator instance to which handle refers.
     */
    double statsCalcGetStdDev(int handle);

#ifdef __cplusplus
}
#endif // __cplusplus was defined

#endif /* End #ifndef STATSCALCULATOR_H preprocessor conditional block. */
