/**
 * @file    poly.cpp
 * @brief   This class represents a polynomial, stored in a dynamically-
 *          allocated array of ints. The content of an elements represents a
 *          coefficient and the index represents a power, so Poly[5] = 4 means
 *          4x^5. Only non-negative exponents are allowed. Constructors are
 *          provided to create polynomials with one element set. Mutators are
 *          provided to change elements one-at-a-time, or set all elements
 *          according to a list provided in an istream. Accessors are provided
 *          to retrieve a coefficient at a specific element, or print a human-
 *          readable representation of the polynomial to an ostream. Operators
 *          are overloaded for addition, subtraction, multiplication,
 *          assignment (including combined with the previous three), equality,
 *          and iostreams.
 * @author  Brendan Sweeney, SID 1161837
 * @date    January 11, 2012
 */

#include "poly.h"

/**----------------------------------------------------------------------------
 * Default constructor. Creates a Poly of size 1 with the x^0 coefficient set
 * to 0.
 * @pre None.
 * @post Poly has size 1 and its first element is 0
 */
Poly::Poly() : size(1)
{
    coeffList = new int[size];
    coeffList[0] = 0;
} // end Default Constructor

/**----------------------------------------------------------------------------
 * Single parameter constructor. Creates a Poly of size 1 with the x^0
 * coefficient set to a specified value.
 * @param coeff  The coefficient of the x^0 value.
 * @pre None.
 * @post Poly has size 1 and its first element is equal to coeff.
 */
Poly::Poly(int coeff) : size(1)
{
    coeffList = new int[size];
    coeffList[0] = coeff;
} // end 1 Parameter Constructor

/**----------------------------------------------------------------------------
 * Double parameter constructor. Creatse a Poly of size determined by exp with
 * the last element set to a specified value.
 * @param coeff  The coefficient of the final element of the Poly.
 * @param exp  The power (index) of the last element of the Poly; its largest
 *             exponent. Only the absolute value of exp is used.
 * @pre None.
 * @post Poly has size greater than exp and its last element is equal to coeff.
 *       any earlier elements are equal to 0.
 */
Poly::Poly(int coeff, int exp)
{
    if (exp < 0)
    {
        size = exp * -1 + 1;
    }
    else
    {
        size = exp + 1;
    } // end if (exp < 0)

    coeffList = new int[size];

    for (int i = 0; i < size - 1; ++i)
    {
        coeffList[i] = 0;
    } // end for (int i = 0)

    coeffList[size - 1] = coeff;
} // end 2 Parameter Constructor

/**----------------------------------------------------------------------------
 * Copy constructor. Creates a Poly that is an exact copy of the parameter.
 * @param orig  The original Poly to copy.
 * @pre None.
 * @post The new Poly is an exact copy of orig.
 */
Poly::Poly(const Poly& orig) : size(orig.size)
{
    coeffList = new int[size];

    for (int i = 0; i < size; ++i)
    {
        coeffList[i] = orig.coeffList[i];
    } // end for (int i = 0)
} // end Copy Constructor

/**----------------------------------------------------------------------------
 * Destructor. Sets each element to 0 before deleting the array. size is set to
 * 0 and the pointer coeffList is set to NULL for uniformity.
 * @pre None.
 * @post All allocated resources are returned to the system.
 */
Poly::~Poly()
{
    for (int i = 0; i < size; ++i)
    {
        coeffList[i] = 0;
    } // end for (int i = 0)

    size = 0;
    delete [] coeffList;
    coeffList = NULL;
} // end Destructor

/**----------------------------------------------------------------------------
 * Overloaded + operator. Adds this Poly to another and returns the result.
 * @param rhs  The Poly to be added to this one.
 * @pre None.
 * @post This Poly and rhs remain unchanged.
 * @return A Poly that is the sum of this one and rhs.
 */
Poly Poly::operator+(const Poly& rhs) const
{
    // copy the larger Poly, then add the smaller one
    if (size > rhs.size)
    {
        Poly sum(*this);

        for (int i = 0; i < rhs.size; ++i)
        {
            sum.coeffList[i] += rhs.coeffList[i];
        } // end for (int i = 0)

        return sum;
    }
    else
    {
        Poly sum(rhs);

        for (int i = 0; i < size; ++i)
        {
            sum.coeffList[i] += coeffList[i];
        } // end for (int i = 0)

        return sum;
    } // if (size > rhs.size)
} // end operator+(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded - operator. Subtracts another Poly from this one and returns the
 * result.
 * @param rhs  The Poly to be subtracted from this one.
 * @pre None.
 * @post This Poly and rhs remain unchanged.
 * @return A Poly that is the difference between this one and rhs.
 */
Poly Poly::operator-(const Poly& rhs) const
{
    Poly diff(*this);

    // ensure new Poly is large enough
    if (size < rhs.size)
    {
        diff.setCoeff(0, rhs.size - 1);
    } // end if (size < rhs.size)

    for (int i = 0; i < rhs.size; ++i)
    {
        diff.coeffList[i] -= rhs.coeffList[i];
    } // end for (int i = 0)

    return diff;
} // end operator-(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded * operator. Multiplies this Poly with another one and returns the
 * result.
 * @param rhs  The Poly to be multiplied with this one.
 * @pre None.
 * @post This Poly and rhs remain unchanged.
 * @return A poly that is the product of this one and rhs.
 */
Poly Poly::operator*(const Poly& rhs) const
{
    Poly prod;

    // support largest power
    prod.setCoeff(0, size + rhs.size - 2);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < rhs.size; ++j)
        {
            prod.coeffList[i + j] += coeffList[i] * rhs.coeffList[j];
        } // end for (int j = 0)
    } // end for (int i = 0)

    return prod;
} // end operator*(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded = operator. Sets this Poly to the same values as another one.
 * @param rhs  The original Poly to copy.
 * @pre None.
 * @post This Poly is equal to rhs.
 * @return A reference to this Poly.
 */
Poly& Poly::operator=(const Poly& rhs)
{
    if (this != &rhs)
    {
        delete [] coeffList;
        size = rhs.size;
        coeffList = new int[size];

        for (int i = 0; i < size; ++i)
        {
            coeffList[i] = rhs.coeffList[i];
        } // end for (int i = 0)
    } // end if (this != &rhs)

    return *this;
} // end operator=(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded += operator. Adds another Poly to this one.
 * @param rhs  The Poly to be added to this one.
 * @pre None.
 * @post The polynomial value of rhs has been added to this Poly.
 * @return A reference to this Poly, the sum of the input.
 */
Poly& Poly::operator+=(const Poly& rhs)
{
    if (size < rhs.size)
    {
        setCoeff(0, rhs.size - 1);
    } // end if (size < rhs.size)

    for (int i = 0; i < size; ++i)
    {
        coeffList[i] += rhs.coeffList[i];
    } // end for (int i = 0)

    return *this;
} // end operator+=(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded -= operator. Subtracts another Poly from this one.
 * @param rhs  The Poly to be subtracted from this one.
 * @pre None.
 * @post The polynomial value of rhs has been subtracted from this Poly.
 * @return A reference to this Poly, the difference of the input.
 */
Poly& Poly::operator-=(const Poly& rhs)
{
    if (size < rhs.size)
    {
        setCoeff(0, rhs.size - 1);
    } // end if (size < rhs.size)

    for (int i = 0; i < size; ++i)
    {
        coeffList[i] -= rhs.coeffList[i];
    } // end for (int i = 0)

    return *this;
} // end operator-=(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded *= operator. Multiplies another Poly with this one.
 * @param rhs  The Poly to be multiplied with this one.
 * @pre None.
 * @post The polynomial value of rhs has been multiplied with this Poly.
 * @return A reference to this Poly, the product of the input.
 */
Poly& Poly::operator*=(const Poly& rhs)
{
    int *prod = new int[size + rhs.size - 1];

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < rhs.size; ++j)
        {
            prod[i + j] += coeffList[i] * rhs.coeffList[j];
        } // end for (int j = 0)
    } // end for (int i = 0)

    delete [] coeffList;
    coeffList = prod;
    prod = NULL;

    return *this;
} // end operator*=(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded == operator. Tests if the polynomial represented by this Poly is
 * equivalet to the polynomial represented by another Poly. Calls compare().
 * @param rhs  The Poly to compare with this one.
 * @pre None.
 * @post None.
 * @return true if the polynomial represented by this Poly is the same as that
 *         of rhs; false, otherwise.
 */
bool Poly::operator==(const Poly& rhs) const
{
    if (size > rhs.size)
    {
        return compare(rhs, *this);
    }
    else
    {
        return compare(*this, rhs);
    }

    return true;
} // end operator==(const Poly&)

/**----------------------------------------------------------------------------
 * Overloaded == operator. Tests if the polynomial represented by this Poly is
 * not equivalet to the polynomial represented by another Poly.
 * @param rhs  The Poly to compare with this one.
 * @pre None.
 * @post None.
 * @return true if the polynomial represented by this Poly is different from
 *         that of rhs; false, otherwise.
 */
bool Poly::operator!=(const Poly& rhs) const
{
    return !(*this == rhs);
} // end operator!=(const Poly&)

/**----------------------------------------------------------------------------
 * Accessor for an element of the coefficient list.
 * @param exp  The power (index) of the element whose coefficient is sought.
 * @pre exp is within the range of the coefficient list.
 * @post This Poly remains unchanged.
 * @return The coefficient of the indicated power if exp is within range of the
 *         coefficient list; 0, otherwise.
 */
int Poly::getCoeff(int exp) const
{
    if (exp >= size || exp < 0)
    {
        return 0;
    } // end if (exp >= size)

    return coeffList[exp];
} // end getCoeff(int)

/**----------------------------------------------------------------------------
 * Mutator to set an element of the coefficient list.
 * @param coeff  The new coefficient of the indicated power.
 * @param exp  The power (index) of the element of the Poly to set. Only the
 *             absolute value of exp is used.
 * @pre None.
 * @post This Poly has the identified power set to the specified coefficient.
 *       If the identified power was outside of the range of the coefficient
 *       list, the list is expanded to accommodate it and all other new
 *       elements are set to 0.
 */
void Poly::setCoeff(int coeff, int exp)
{
    int index = exp, *temp;

    if (exp < 0)
    {
        index *= -1;
    } // end if (exp < 0)

    // handle new boundary
    if (index >= size)
    {
        temp = new int[index + 1];

        for (int i = 0; i < size; ++i)
        {
            temp[i] = coeffList[i];
        } // end for (int i = 0)

        delete [] coeffList;
        coeffList = temp;

        while(size < index)
        {
            coeffList[size++] = 0;
        } // end while(size < index)

        ++size;
    } // end if (index >= size)

    coeffList[index] = coeff;
    temp = NULL;
} // end setCoeff(int, int)

/**----------------------------------------------------------------------------
 * Overloaded << operator. Writes the contents of this Poly to an ostream. Only
 * elements with a non-zero coefficient are displayed. x is displayed for all
 * powers greater than 0. For powers greater than 1, x is shown as x^y, where y
 * is the power. Positive value are prefixed with +. If there are no elements
 * to display, " 0" is written out.
 * @param output  The ostream to which to write out the polynomial.
 * @param source  The Poly from which to read a coefficient list (usually this
 *                Poly).
 * @pre None.
 * @post The ostream contains a string representing this Poly. This Poly
 *       remains unchanged.
 * @return A reference to the supplied ostream, containing a polynomial string.
 */
ostream& operator<<(ostream& output, const Poly& source)
{
    // to check special case of polynomial with all coefficients equal to 0
    bool nonzero = false;

    for (int i = source.size - 1; i >= 0; --i)
    {
        // only act if a non-zero coefficient is found
        if (source.coeffList[i] != 0)
        {
            nonzero = true;
            cout << ' ';
            
            if (source.coeffList[i] > 0)
            {
                cout << '+';
            } // end if (source.coeffList[i] > 0)

            cout << source.coeffList[i];

            if (i > 0)
            {
                cout << 'x';
            } // end if (i > 0)

            if (i > 1)
            {
                cout << '^' << i;
            } // end if (i > 1)
        } // end if (source->coeffList[i] != 0)
    } // end for (int i = 0)

    if (!nonzero)
    {
        cout << " 0";
    } // end if (!nonzero)

    return output;
} // end operator<<(ostream&, Poly&)

/**----------------------------------------------------------------------------
 * Overloaded >> operator. Reads a coefficient list from the supplied istream
 * and stores it in this Poly. Elements are read in pairs; the first digit is
 * the coefficient, the second digit is the power (index). Terminates when a
 * pair of 0 0 is encountered.
 * @param input  The istream from which to read the coefficient list.
 * @param target  The Poly to which to write the coefficient list (usually this
 *                Poly).
 * @pre input contains a series of integers, separated by white space, in pairs
 *      eventually ending in 0 0.
 * @post The integer pairs up to 0 0 have been removed from the supplied
 *       istream. The coefficient list of target matches that supplied by the
 *       input istream.
 * @return A reference to the supplied istream, less a string of integers.
 */
istream& operator>>(istream& input, Poly& target)
{
    int coeff, exp;
    input >> coeff >> exp;

    // set all current elements to 0
    for (int i = 0; i < target.size; ++i)
    {
        target.coeffList[i] = 0;
    } // end for (int i = 0)

    while(coeff != 0 || exp != 0)
    {
        target.setCoeff(coeff, exp);
        input >> coeff >> exp;
    } // end while(coeff != 0)

    return input;
} // end operator>>(istream&, Poly&)

/**----------------------------------------------------------------------------
 * Compares the coefficient list of two Poly objects of possibly different
 * sizes. They are considered equivalent if all the elements in the smaller
 * Poly match the beginning elements in the larger Poly and all of the later
 * elements in the larger Poly are equal to 0.
 * @param smaller  The Poly with the smaller size. May be the same as larger,
 *                 but cannot be greater.
 * @param larger  The Poly with the larger size. May be the same as smaller,
 *                but cannot be less.
 * @pre The size of smaller is less than or equal to the size of larger.
 * @post smaller and larger remain unchanged.
 * @return true if both parameters represent equivalent polynomials; false,
 *         otherwise.
 */
bool Poly::compare(const Poly& smaller, const Poly& larger) const
{
    int i = 0;

    while(i < smaller.size)
    {
        if (smaller.coeffList[i] != larger.coeffList[i])
        {
            return false;
        } // end if (smaller.coeffList[i] != larger.coeffList[i])

        ++i;
    } // end while(i < smaller.size)

    while(i < larger.size)
    {
        if (larger.coeffList[i] != 0)
        {
            return false;
        } // end if (larger.coeffList[i] != 0)

        ++i;
    } // end while(i < larger.size)

    return true;
} // end compare (const Poly&, const Poly&)
