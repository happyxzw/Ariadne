/***************************************************************************
 *            test.h
 *
 *  Copyright  2007  Alberto Casagrande, Pieter Collins, Ivan S. Zapreev
 *  casagrande@dimi.uniud.it, pieter.collins@cwi.nl, ivan.zapreev@gmail.com
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*!\file test.h
 * \brief Macros for test suite.
 */

#ifndef ARIADNE_TEST_H
#define ARIADNE_TEST_H

#include <iostream>
#include <exception>

int ARIADNE_TEST_FAILURES=0;
int ARIADNE_TEST_SKIPPED=0;

// This needs to be a function since we do not want to evaluate the result twice,
// and can't store it in a variable since we don't know it's type.
template<class R, class ER>
bool
ariadne_check(std::ostream& os, const R& r, const ER& er) {
    os << r << std::flush; return (r==er);
}

//This is the variable that stores counter for the number of test cases
//The value is used and updated in the next two macro definitions
int test_case_counter = 0;

/*! \brief Print the title for the test case */
#define ARIADNE_PRINT_TEST_CASE_TITLE( pTitle )                         \
    {                                                                   \
        cout << endl << "***" << ++test_case_counter << ": "<< pTitle << "***" << endl; \
        cout.flush();                                                   \
    }                                                                   \


/*! \brief Print the comment for the test */
#define ARIADNE_PRINT_TEST_COMMENT( pComment )                          \
    {                                                                   \
        cout << "* COMMENT: " << pComment << "" << endl;                \
        cout.flush();                                                   \
    }                                                                   \


/*! \brief Print the comment for the test */
#define ARIADNE_TEST_WARN( message )                                    \
    {                                                                   \
        cout << "WARNING: " << message << "" << endl;                \
        cerr << "WARNING: " << message << "" << endl;                \
    }                                                                   \


/*! \brief Catches an exception and writes a diagnostic to standard output and standard error. */
#define ARIADNE_TEST_CATCH(message)                                     \
    catch(const std::exception& e) {                                    \
        ++ARIADNE_TEST_FAILURES;                                        \
        std::cout << "exception: \"" << e.what() << "\"\n" << std::endl; \
        std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": " << message << " throwed \"" << e.what() << "\"." << std::endl;     \
    }                                                                   \
    catch(...) {                                                        \
        ++ARIADNE_TEST_FAILURES;                                        \
        std::cout << "unknown exception\n" << std::endl;                \
        std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": " << message << " throwed an unknown exception." << std::endl;       \
    }                                                                   \


/*! \brief Calls a function */
#define ARIADNE_TEST_CALL(function)                                     \
    {                                                                   \
        std::cout << "****************************************\n"       \
                  << "CALLING " << #function << "\n"                    \
                  << "****************************************\n" << std::endl; \
        try {                                                           \
            function;                                                   \
        } catch(const std::exception& e) {                              \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "ERROR: exception in " << #function << ": "    \
                      << e.what() << std::endl;                         \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": calling " \
                      << #function << ": " << e.what() << std::endl; \
            std::cout << std::endl;                                     \
        }                                                               \
    }                                                                   \


/*! \brief Omits a test, with a warning message */
#define ARIADNE_TEST_SKIP(function)                                     \
    {                                                                   \
        std::cout << "****************************************\n"       \
                  << "SKIPPING " << #function << "\n"                   \
                  << "****************************************\n" << std::endl; \
        ++ARIADNE_TEST_SKIPPED;                                         \
        std::cout << std::endl;                                         \
    }                                                                   \


/*! \brief Executes \a statement, writing the statement to standard output. Does not check for any errors. */
#define ARIADNE_TEST_EXECUTE(statement)                                 \
    {                                                                   \
        std::cout << #statement << ": " << std::flush;                  \
        statement;                                                      \
        std::cout << " (ok)\n" << std::endl;                            \
    }                                                                   \


/*! \brief Tries to execute \a statement, writing the statement to standard output. Writes a diagnostic report to standard error if an exception is thrown. <br> <b>Important:</b> Use the ARIADNE_TEST_CONSTRUCT() macro if \a statement declares a variable and calls a constructor. */
#define ARIADNE_TEST_TRY(statement)                                     \
    {                                                                   \
        std::cout << #statement << ": " << std::flush;                  \
        try {                                                           \
            statement;                                                  \
            std::cout << " (ok)\n" << std::endl;                        \
        }                                                               \
            ARIADNE_TEST_CATCH("Statement `" << #statement << "'")      \
        }                                                               \


/*! \brief Writes the expression to the output. Does not catch errors. */
#define ARIADNE_TEST_PRINT(expression)                                  \
    {                                                                   \
        std::cout << #expression << " = " << std::flush;                \
        std::cout << (expression) << "\n" << std::endl;                 \
    }                                                                   \


/*! \brief Tries to evaluate \a expression, writing the expression and the result to standard ouput. Writes a diagnostic report to standard error if an exception is thrown., prints the result and gives a diagnostic if an exception is thrown. */
#define ARIADNE_TEST_EVALUATE(expression)                               \
    {                                                                   \
        std::cout << #expression << ": " << std::flush;                 \
        try {                                                           \
            std::cout << (expression) << "\n" << std::endl;             \
        }                                                               \
            ARIADNE_TEST_CATCH("Expression `" << #expression << "'")    \
        }                                                               \


/*! \brief Evaluates \a expression in a boolean context and checks if the result is \a true. */
#define ARIADNE_TEST_ASSERT(expression)                                 \
    {                                                                   \
        std::cout << #expression << ": " << std::flush;                 \
        bool result = (expression);                                     \
        if(result) {                                                    \
            std::cout << "true\n" << std::endl;                         \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: false" << std::endl;                 \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__ << ": Assertion `" << #expression << "' failed." << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Evaluates \a expression and checks if the result is equal to \a expected. */
#define ARIADNE_TEST_CHECK(expression,expected)                         \
    {                                                                   \
        std::cout << #expression << ": " << std::flush; \
        bool ok = ariadne_check(std::cout,expression,expected);         \
        if(ok) {                                                        \
            std::cout << "\n" << std::endl;                             \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: expected " << #expression << " = " << #expected << " = " << (expected) << " \n" << std::endl; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Check `" << #expression << "==" << #expected << "' failed." << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Evaluates \a expression and checks if the result is equal to \a expected. */
#define ARIADNE_TEST_EQUAL(expression1,expression2)                         \
    {                                                                   \
        std::cout << #expression1 << " == " << #expression2 << ": " << std::flush; \
        bool ok = (expression1) == (expression2);                       \
        if(ok) {                                                        \
            std::cout << "true\n" << std::endl;                         \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: " << #expression1 << ":\n           " << (expression1) \
                      << "\n     : " << #expression2 << ":\n           " << (expression2) << std::endl; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Equality `" << #expression1 << " == " << #expression2 << "' failed; " << #expression1 << "=" << (expression1) << "; " << #expression2 << "=" << (expression2) << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Evaluates \a expression and checks if the result is equal to \a expected. */
#define ARIADNE_TEST_UNARY_PREDICATE(predicate,argument)    \
    {                                                                   \
        std::cout << #predicate << "(" << #argument << ") with " << #argument << "=" << (argument) << ": " << std::flush; \
        bool ok = predicate((argument));                  \
        if(ok) {                                                        \
            std::cout << "true\n" << std::endl;                         \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: false" << std::endl;                 \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Predicate `" << #predicate << "(" << #argument << ")' with " << #argument << "=" << (argument) << " is false." << std::endl; \
        }                                                               \
    }


/*! \brief Evaluates \a expression and checks if the result is equal to \a expected. */
#define ARIADNE_TEST_BINARY_PREDICATE(predicate,argument1,argument2)    \
    {                                                                   \
        std::cout << #predicate << "(" << (#argument1) << "," << (#argument2) << ") with " << #argument1 << "=" << (argument1) << ", " << #argument2 << "=" << (argument2) << ": " << std::flush; \
        bool ok = predicate((argument1),(argument2));                  \
        if(ok) {                                                        \
            std::cout << "true\n" << std::endl;                         \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: false" << std::endl;                 \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Predicate `" << #predicate << "(" << #argument1 << "," << #argument2 << ")' with " << #argument1 << "=" << (argument1) << "; " << #argument2 << "=" << (argument2) << " is false." << std::endl; \
        }                                                               \
    }


/*! \brief Evaluates \a expression and checks if the result compares correctly with \a expected. */
#define ARIADNE_TEST_COMPARE(expression,comparison,expected)           \
    {                                                                   \
        std::cout << #expression << ": " << (expression) << std::flush; \
        bool ok = ((expression) comparison (expected));               \
        if(ok) {                                                        \
            std::cout << " " << #comparison << " " << (expected) << ": true\n" << std::endl; \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: expected: " << #expression << #comparison << #expected << "=" << (expected) << std::endl; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Comparison `" << #expression << #comparison << #expected << "' failed; " << #expression << "=" << (expression) << "; " << #expected << "=" << (expected) << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Evaluates \a expression and checks if the result compares correctly with \a expected. */
#define ARIADNE_TEST_RESULT_COMPARE(type,expression,comparison,expected) \
    {                                                                   \
        type result=(expression);                                       \
        std::cout << #expression << ": " << result << std::flush; \
        bool ok = result comparison (expected);               \
        if(ok) {                                                        \
            std::cout << " " << #comparison << " " << (expected) << "\n" << std::endl; \
        } else {                                                        \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: expected: " << #expression << #comparison << #expected << std::endl; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Comparison `" << #expression << #comparison << #expected << "' failed; " << #expression << "=" << result << "; " << #expected << "=" << (expected) << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Declares an object \a variable of type \a class (uses the default constructor). */
#define ARIADNE_TEST_DECLARE(class,variable)                            \
    {                                                                   \
        std::cout << #class << " " << #variable << ": " << std::flush;  \
        try {                                                           \
            class variable;                                             \
            std::cout << #variable << "==" << variable << "\n" << std::endl; \
        }                                                               \
        ARIADNE_TEST_CATCH("Constructor `" << #class << "" << #variable << "'") \
    }                                                                   \
    class variable;                                                     \


/*! \brief Constructs object \a variable of type \a class from \a expression. */
#define ARIADNE_TEST_CONSTRUCT(class,variable,expression)               \
    {                                                                   \
        std::cout << #class << " " << #variable << "" << #expression << ": " << std::flush; \
        try {                                                           \
            class variable expression;                                  \
            std::cout << #variable << "==" << variable << "\n" << std::endl; \
        }                                                               \
        ARIADNE_TEST_CATCH("Constructor `" << #class << "" << #variable << "" << #expression << "'") \
    }                                                                   \
    class variable expression;                                          \


/*! \brief Constructs object \a variable of type \a class from \a expression. */
#define ARIADNE_TEST_NAMED_CONSTRUCT(class,variable,expression)               \
    {                                                                   \
        std::cout << #class << " " << #variable << "=" << #class << "::" << #expression << ": " << std::flush; \
        try {                                                           \
            class variable = class :: expression;                                  \
            std::cout << #variable << "==" << variable << "\n" << std::endl; \
        }                                                               \
        ARIADNE_TEST_CATCH("Named constructor `" << #class << "" << #variable << "=" << #class << "::" << #expression << "'") \
    }                                                                   \
    class variable = class :: expression;                                          \


/*! \brief Assigns object \a variable from \a expression. */
#define ARIADNE_TEST_ASSIGN(variable, expression)                       \
    {                                                                   \
        std::cout << #variable << "=" << #expression << ": " << std::flush; \
        try {                                                           \
            variable=(expression);                                      \
            std::cout << variable << "\n" << std::endl;                 \
        }                                                               \
        ARIADNE_TEST_CATCH("Assignment `" << #variable << "=" << #expression << "'") \
            }                                                           \


/*! \brief Evaluates expression and expects an exception. */
#define ARIADNE_TEST_THROWS(statement,error)                             \
    {                                                                   \
        std::cout << #statement << ": " << std::flush;                  \
        try {                                                           \
            statement;                                                  \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: expected " << #error << "; no exception thrown\n"; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": expected " << #error << "; no exception thrown." << std::endl; \
        }                                                               \
        catch(const error& e) {                                         \
            std::cout << "caught " << #error << " as expected\n" << std::endl; \
        }                                                               \
        catch(const std::exception& e) {                                \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: caught exception " << e.what() << "; expected " << #error << "\n"; \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": caught exception " << e.what() << "; expected " << #error << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Evaluates expression and expects an exception. */
#define ARIADNE_TEST_FAIL(statement)                                    \
    {                                                                   \
        std::cout << #statement << ": " << std::flush;                  \
        try {                                                           \
            statement;                                                  \
            ++ARIADNE_TEST_FAILURES;                                    \
            std::cout << "\nERROR: expected exception; none thrown\n";  \
            std::cerr << "ERROR: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": expected exception; no exception thrown." << std::endl; \
        }                                                               \
        catch(...) {                                                    \
            std::cout << "caught exception as expected\n" << std::endl; \
        }                                                               \
    }                                                                   \


/*! \brief Check the iterator of the GridTreeSudset by iterating through all it's values and
 * comparing them with the valus in the vector \a expected_result, the total number of iterated
 * elements should coincide with the value of \a expected_number_elements
 */
#define ARIADNE_TEST_GRID_TREE_SUBSET_ITERATOR( expected_result, theGridTreeSubset, expected_number_elements ) \
    {                                                                   \
        int elements_count = 0;                                         \
        for (GridTreeSubset::const_iterator it = theGridTreeSubset.begin(), end = theGridTreeSubset.end(); it != end; it++, elements_count++) { \
            if( elements_count < expected_number_elements ) {           \
                ARIADNE_PRINT_TEST_COMMENT("The next iterator node is: "); \
                ARIADNE_TEST_COMPARE( (*expected_result[elements_count]), == , (*it) ); \
            }                                                           \
        }                                                               \
        ARIADNE_PRINT_TEST_COMMENT("Test that we iterated through the right number of nodes"); \
        ARIADNE_TEST_EQUAL( elements_count , expected_number_elements ); \
    }                                                                   \


/*! \brief clean std::vector, i.e. delete memory of it's non NULL elements and set them to NULL in the vector */
#define ARIADNE_CLEAN_TEST_VECTOR( vector ) \
    { \
        for(uint i = 0; i < vector.size(); i++ ) { \
            if( vector[i] != NULL ) { \
                delete vector[i]; vector[i] = NULL; \
            } \
        } \
    } \


#endif // ARIADNE_TEST_H

