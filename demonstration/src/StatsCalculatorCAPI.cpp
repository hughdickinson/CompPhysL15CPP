/** \file StatsCalculatorCAPI.cpp Definition of the C API for the StatsCalculator class.
 *
 * This file provides definitions of functions comprising the C API for the StatsCalculator
 * class. It contains C++-only language constructs and should be compiled using a C++
 * compiler.
 */

// PROJECT HEADERS
/* The "StatsCalculator.h" header file provides declarations of the C API functions
 * and the StatsCalculator class.
 */
#include "StatsCalculator.h"

// STL HEADERS
// The <map> header provides the std::map ASSOCIATIVE container type
#include <map>

/** Declare a "global" std::map that associates integer "handles" with instances of StatsCalculator
 * This will permit C code to instantiate and access StatsCalulator objects without
 * having to directly reference them.
 */
std::map<int, StatsCalculator> statsCalculators;

/* The subsequent code provides the DEFINITIONS of the C API functions. The definitions include
 * C++-only language constructs and must be compiled with a C++ compiler. However, mangling of
 * the function identifiers must be suppressed by prepending them with the 'extern "C"' token pair.
 */

/** Instantiates a StatsCalculator object and appends it to the global "statsCalculators" std::map
 * using a new integer key equal to one greater than the highest key value currently stored.
 * The elements of std::maps are std::pair types. A std:pair is a special container with exactly two elements
 *
 * The keys of the map are stored as the first element of each pair and the associated values are stored as
 * the second element of the pair.
 *
 * The elements of a std::map are stored in key-sorted order, so the largest key will correspond to the
 * last element of the map. If the map is NOT empty, this is obtained by dereferencing the iterator
 * returned by the rbegin() ("reverse begin") method of std::map, and extracting the first element of
 * the std::pair instance that is returned. If the map IS empty, dereferencing the iterator will generate
 * a segmentation fault, so a default zero-valued key is used.
 *
 * The new element is inserted into the map using the emplace_hint() method provided by std::map,
 * which returns an iterator corresponding to the std::pair that was inserted. The C API function
 * then dereferences the iterator and returns the first element of the std::pair.
 *
 * Since the keys of a std::map must be unique, the returned integer provides a unique handle to a
 * particular StatsCalculator instance.
 *
 * \return An integer "handle" that uniquely refers to the instantiated
 * StatsCalculator object.
 */
extern "C" int statsCalcCreate(){
    // Compute an appropriate key to associate with a new StatsCalculator instance.
    int key = statsCalculators.empty() ? 0 : statsCalculators.rbegin()->first + 1;
    /* Construct a new std::pair<int, StatsCalculator> and insert it into the global "statsCalculators"
     * std::map.
     *
     * If the insertion is successful, an immutable iterator corresponding to the inserted element is
     * returned. Dereferencing this iterator returns an immutable reference to the ELEMENT, which
     * corresponds to a key-value pair.
     */
    const std::pair<int, StatsCalculator> & created = *statsCalculators.emplace_hint(statsCalculators.end(), std::make_pair(key, StatsCalculator()));
    /* return the first element of the inserted std::pair, which corresponds to a unique integer
     * key.
     */
    return created.first;
}

/** Searches the global "statsCalculators" for an element corresponding to the integer
 * handle that is provided as the function argument. If the corresponding element is
 * found, it is destroyed. Otherwise this function is a no-op.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be destroyed.
 */
extern "C" void statsCalcDestroy(int handle){
    std::map<int, StatsCalculator>::iterator handlePos = statsCalculators.find(handle);
    if(handlePos != statsCalculators.end()){
        statsCalculators.erase(handlePos);
    }
}

/** \brief Expose the functionality of StatsCalculator::appendValue() in the
 * C API.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to parse the file.
 * \param value - A double precision value to append to the "numericValues"
 * member datum of the StatsCalculator instance to which handle refers.
 */
;

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it.
 *
 * If the key is valid, the StatsCalculator::appendValue() method is then invoked on the
 * retrieved StatsCalculatorinstance, passing "value" argument.
 * 
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * append "value" to its "numericValues" member datum.
 * \param value - A double precision value to append to the "numericValues"
 * member datum of the StatsCalculator instance to which handle refers.
 */
extern "C" void statsCalcAppendValue(int handle, double value){
    try{
        statsCalculators.at(handle).appendValue(value);
    }
    catch(std::out_of_range & exception){
        // Intentionally take no action.
        return;
    }
}

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it.
 *
 * If the key is valid, StatsCalculator::readFile() method is invoked on the
 * retrieved instance, passing the fileName C-string that was provided as the second
 * function argument.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to parse the file.
 * \param fileName - A C-string specifying the path of the file to be
 * opened and parsed.
 */
extern "C" void statsCalcReadFile(int handle, const char * fileName){
    try{
        statsCalculators.at(handle).readFile(fileName);
    }
    catch(std::out_of_range & exception){
        // Intentionally take no action.
        return;
    }
}

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it.
 *
 * If the key is valid, StatsCalculator::writeStats() method is invoked on the
 * retrieved instance, passing the fileName C-string that was provided as the second
 * function argument.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to write its computed statistics to a file.
 * \param fileName - A C-string specifying the path of the file to be
 * written.
 */
extern "C" void statsCalcWriteStats(int handle, const char * fileName){
    try{
        statsCalculators.at(handle).writeStats(fileName);
    }
    catch(std::out_of_range & exception){
        // Intentionally take no action.
        return;
    }
}

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it and returns a default zero value.
 *
 * If the key is valid, StatsCalculator::getSum() method is invoked on the
 * retrieved instance and its return value is returned by the function.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to return the sum of its stored numeric data.
 *
 * \return The sum of the numeric data stored by the StatsCalculator
 * instance to which handle refers.
 */
extern "C" double statsCalcGetSum(int handle){
    try{
        return statsCalculators.at(handle).getSum();
    }
    catch(std::out_of_range & exception){
        return 0.0;
    }
}

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it and returns a default zero value.
 *
 * If the key is valid, StatsCalculator::getMean() method is invoked on the
 * retrieved instance and its return value is returned by the function.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to return the mean of its stored numeric data.
 *
 * \return The mean of the numeric data stored by the StatsCalculator
 * instance to which handle refers.
 */
extern "C" double statsCalcGetMean(int handle){
    try{
        return statsCalculators.at(handle).getMean();
    }
    catch(std::out_of_range & exception){
        return 0.0;
    }
}

/** Attempts to retrieve a StatsCalculator instance from the global "statsCalculators"
 * that corresponds to  to the integer handle that is provided as the first function
 * argument. If the specified handle is not a key in the map the at() method will
 * raise a std::out_of_range exception. The function catches this exception but (currently)
 * takes no actions to handle it and returns a default zero value.
 *
 * If the key is valid, StatsCalculator::getStandardDeviation() method is invoked on the
 * retrieved instance and its return value is returned by the function.
 *
 * \param handle - an integer that was returned by statsCalcCreate() and
 * uniquely references the instance of StatsCalculator that should
 * be induced to return the mean of its stored numeric data.
 *
 * \return The standard deviation of the numeric data stored by the
 * StatsCalculator instance to which handle refers.
 */
extern "C" double statsCalcGetStdDev(int handle){
    try{
        return statsCalculators.at(handle).getStandardDeviation();
    }
    catch(std::out_of_range & exception){
        return 0.0;
    }
}
