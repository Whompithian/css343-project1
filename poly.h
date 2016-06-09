/**
 * @file    poly.h
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

#ifndef _POLY_H
#define	_POLY_H

#include <iostream>

using namespace std;

class Poly
{
public:
    
    /**------------------------------------------------------------------------
     * Default constructor. Creates a Poly of size 1 with the x^0 coefficient
     * set to 0.
     * @pre None.
     * @post Poly has size 1 and its first element is 0
     */
    Poly();

    /**------------------------------------------------------------------------
     * Single parameter constructor. Creates a Poly of size 1 with the x^0
     * coefficient set to a specified value.
     * @param coeff  The coefficient of the x^0 value.
     * @pre None.
     * @post Poly has size 1 and its first element is equal to coeff.
     */
    Poly(int coeff);
    
    /**------------------------------------------------------------------------
     * Double parameter constructor. Creatse a Poly of size determined by exp
     * with the last element set to a specified value.
     * @param coeff  The coefficient of the final element of the Poly.
     * @param exp  The power (index) of the last element of the Poly; its
     *             largest exponent. Only the absolute value of exp is used.
     * @pre None.
     * @post Poly has size greater than exp and its last element is equal to
     *       coeff. any earlier elements are equal to 0.
     */
    Poly(int coeff, int exp);

    /**------------------------------------------------------------------------
     * Copy constructor. Creates a Poly that is an exact copy of the parameter.
     * @param orig  The original Poly to copy.
     * @pre None.
     * @post The new Poly is an exact copy of orig.
     */
    Poly(const Poly& orig);

    /**------------------------------------------------------------------------
     * Destructor. Sets each element to 0 before deleting the array. size is
     * set to 0 and the pointer coeffList is set to NULL for uniformity.
     * @pre None.
     * @post All allocated resources are returned to the system.
     */
    virtual ~Poly();
    
    /**------------------------------------------------------------------------
     * Overloaded + operator. Adds this Poly to another and returns the result.
     * @param rhs  The Poly to be added to this one.
     * @pre None.
     * @post This Poly and rhs remain unchanged.
     * @return A Poly that is the sum of this one and rhs.
     */
    Poly operator+(const Poly& rhs) const;
    
    /**------------------------------------------------------------------------
     * Overloaded - operator. Subtracts another Poly from this one and returns
     * the result.
     * @param rhs  The Poly to be subtracted from this one.
     * @pre None.
     * @post This Poly and rhs remain unchanged.
     * @return A Poly that is the difference between this one and rhs.
     */
    Poly operator-(const Poly& rhs) const;
    
    /**------------------------------------------------------------------------
     * Overloaded * operator. Multiplies this Poly with another one and returns
     * the result.
     * @param rhs  The Poly to be multiplied with this one.
     * @pre None.
     * @post This Poly and rhs remain unchanged.
     * @return A poly that is the product of this one and rhs.
     */
    Poly operator*(const Poly& rhs) const;
    
    /**------------------------------------------------------------------------
     * Overloaded = operator. Sets this Poly to the same values as another one.
     * @param rhs  The original Poly to copy.
     * @pre None.
     * @post This Poly is equal to rhs.
     * @return A reference to this Poly.
     */
    Poly& operator=(const Poly& rhs);
    
    /**------------------------------------------------------------------------
     * Overloaded += operator. Adds another Poly to this one.
     * @param rhs  The Poly to be added to this one.
     * @pre None.
     * @post The polynomial value of rhs has been added to this Poly.
     * @return A reference to this Poly, the sum of the input.
     */
    Poly& operator+=(const Poly& rhs);
    
    /**------------------------------------------------------------------------
     * Overloaded -= operator. Subtracts another Poly from this one.
     * @param rhs  The Poly to be subtracted from this one.
     * @pre None.
     * @post The polynomial value of rhs has been subtracted from this Poly.
     * @return A reference to this Poly, the difference of the input.
     */
    Poly& operator-=(const Poly& rhs);
    
    /**------------------------------------------------------------------------
     * Overloaded *= operator. Multiplies another Poly with this one.
     * @param rhs  The Poly to be multiplied with this one.
     * @pre None.
     * @post The polynomial value of rhs has been multiplied with this Poly.
     * @return A reference to this Poly, the product of the input.
     */
    Poly& operator*=(const Poly& rhs);
    
    /**------------------------------------------------------------------------
     * Overloaded == operator. Tests if the polynomial represented by this Poly
     * is equivalet to the polynomial represented by another Poly. Calls
     * compare().
     * @param rhs  The Poly to compare with this one.
     * @pre None.
     * @post None.
     * @return true if the polynomial represented by this Poly is the same as
     *         that of rhs; false, otherwise.
     */
    bool operator==(const Poly& rhs) const;
    
    /**------------------------------------------------------------------------
     * Overloaded == operator. Tests if the polynomial represented by this Poly
     * is not equivalet to the polynomial represented by another Poly.
     * @param rhs  The Poly to compare with this one.
     * @pre None.
     * @post None.
     * @return true if the polynomial represented by this Poly is different
     *         from that of rhs; false, otherwise.
     */
    bool operator!=(const Poly& rhs) const;
    
    /**------------------------------------------------------------------------
     * Accessor for an element of the coefficient list.
     * @param exp  The power (index) of the element whose coefficient is
     *             sought.
     * @pre exp is within the range of the coefficient list.
     * @post This Poly remains unchanged.
     * @return The coefficient of the indicated power if exp is within range of
     *         the coefficient list; 0, otherwise.
     */
    int getCoeff(int exp) const;
    
    /**------------------------------------------------------------------------
     * Mutator to set an element of the coefficient list.
     * @param coeff  The new coefficient of the indicated power.
     * @param exp  The power (index) of the element of the Poly to set. Only
     *             the absolute value of exp is used.
     * @pre None.
     * @post This Poly has the identified power set to the specified
     *       coefficient. If the identified power was outside of the range of
     *       the coefficient list, the list is expanded to accommodate it and
     *       all other new elements are set to 0.
     */
    void setCoeff(int coeff, int exp);

    /**------------------------------------------------------------------------
     * Overloaded << operator. Writes the contents of this Poly to an ostream.
     * Only elements with a non-zero coefficient are displayed. x is displayed
     * for all powers greater than 0. For powers greater than 1, x is shown as
     * x^y, where y is the power. Positive value are prefixed with +. If there
     * are no elements to display, " 0" is written out.
     * @param output  The ostream to which to write out the polynomial.
     * @param source  The Poly from which to read a coefficient list (usually
     *                this Poly).
     * @pre None.
     * @post The ostream contains a string representing this Poly. This Poly
     *       remains unchanged.
     * @return A reference to the supplied ostream, containing a polynomial
     *         string.
     */
    friend ostream& operator<<(ostream&, const Poly&);

    /**------------------------------------------------------------------------
     * Overloaded >> operator. Reads a coefficient list from the supplied
     * istream and stores it in this Poly. Elements are read in pairs; the
     * first digit is the coefficient, the second digit is the power (index).
     * Terminates when a pair of 0 0 is encountered.
     * @param input  The istream from which to read the coefficient list.
     * @param target  The Poly to which to write the coefficient list (usually
     *                this Poly).
     * @pre input contains a series of integers, separated by white space, in
     *      pairs eventually ending in 0 0.
     * @post The integer pairs up to 0 0 have been removed from the supplied
     *       istream. The coefficient list of target matches that supplied by
     *       the input istream.
     * @return A reference to the supplied istream, less a string of integers.
     */
    friend istream& operator>>(istream&, Poly&);

private:
    
    /**------------------------------------------------------------------------
     * Compares the coefficient list of two Poly objects of possibly different
     * sizes. They are considered equivalent if all the elements in the smaller
     * Poly match the beginning elements in the larger Poly and all of the
     * later elements in the larger Poly are equal to 0.
     * @param smaller  The Poly with the smaller size. May be the same as
     *                 larger, but cannot be greater.
     * @param larger  The Poly with the larger size. May be the same as
     *                smaller, but cannot be less.
     * @pre The size of smaller is less than or equal to the size of larger.
     * @post smaller and larger remain unchanged.
     * @return true if both parameters represent equivalent polynomials; false,
     *         otherwise.
     */
    bool compare(const Poly& smaller, const Poly& larger) const;
    
    int *coeffList;
    int size;
};

#endif	/* _POLY_H */
