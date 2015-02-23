/***************************************************************************
 *            grid.h
 *
 *  Copyright  2008-9  Ivan S. Zapreev, Pieter Collins
 *            ivan.zapreev@gmail.com, pieter.collins@cwi.nl
 *
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
 *  Foundation, Inc., 59 Templece Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*! \file grid.h
 *  \brief Coordinate-aligned grids.
 */

#ifndef ARIADNE_GRID_H
#define ARIADNE_GRID_H

namespace Ariadne {

template<class T> class Vector;
class Box;

/*! \brief An infinite, uniform grid of rectangles in Euclidean space.
 *  
 *  \internal Maybe a Grid should be a type of Paving or Cover. 
 *  Then rather than having GridXXX classes, we can have classes such that cells of
 *  some type are mapped into concrete sets by a Paving or Cover.
 *  This should be more general, and will unify the concepts of Paving and Cover,
 *  as well as different types of covers.
 */
class Grid {
    typedef double dyadic_type;
    typedef int integer_type;
    typedef Float real_type;
  private:
    // Structure containing actual data values
    struct Data { 
        Vector<Float> _origin; 
        Vector<Float> _lengths; 
    };
  public:
    //! Destructor.
    ~Grid();
                
    //! Default constructor constructs a grid from a null pointer. Needed for some iterators.
    explicit Grid();
                
    //! Construct from a dimension and a spacing in each direction. 
    explicit Grid(uint d);
                
    //! Construct from a dimension and a spacing in each direction. 
    explicit Grid(uint d, Float l);
                
    //! Construct from a vector of offsets.
    explicit Grid(const Vector<Float>& lengths);
                
    //! Construct from a centre point and a vector of offsets.
    explicit Grid(const Vector<Float>& origin, const Vector<Float>& lengths);
                
    //! Copy constructor. Copies a reference to the grid data.
    Grid(const Grid& g);
                
    //! The underlying dimension of the grid.
    uint dimension() const;
                
    //! Tests equality of two grids. Tests equality of references first.
    bool operator==(const Grid& g) const;
                
    //! Tests inequality of two grids.
    bool operator!=(const Grid& g) const;
                
    //! The origin of the grid.
    const Vector<Float>& origin() const;
                
    //! The strides between successive integer points.
    const Vector<Float>& lengths() const;

    //! Set the origin of the grid.
    void set_origin(const Vector<Float>& origin);

    //! Set the \a i-th coordinate of the origin
    void set_origin_coordinate(uint i, Float o);

    //! Set the  strides between successive integer points.
    void set_lengths(const Vector<Float>& lenghts);

    //! Set the \a i-th component of the lenghts
    void set_length(uint i, Float l);

    //! Write to an output stream.
    friend std::ostream& operator<<(std::ostream& os, const Grid& g);

    Float coordinate(uint d, dyadic_type x) const;
    Float subdivision_coordinate(uint d, dyadic_type x) const;
    Float subdivision_coordinate(uint d, integer_type n) const; 

    int subdivision_index(uint d, const Float& x) const; 
    int subdivision_lower_index(uint d, const Float& x) const; 
    int subdivision_upper_index(uint d, const Float& x) const; 

    array<double> index(const Vector<Float>& pt) const;
    array<double> lower_index(const Vector<Interval>& bx) const;
    array<double> upper_index(const Vector<Interval>& bx) const;

    Vector<Float> point(const array<int>& a) const;
    Vector<Float> point(const array<double>& a) const;
    Vector<Interval> box(const array<double>& l, const array<double>& u) const;
    Vector<Interval> cell(const array<int>& a) const;
    Box primary_cell() const;
  private:
    // Create new data
    void _create(const Vector<Float>& o, const Vector<Float>& l);
  private:
    // Pointer to data. We can test grids for equality using reference semantics since data is a constant.
    // boost::shared_ptr<Data> _data;
    // WRONG! By using references, modifications are not local to the current instance. Using simple data instead.
    Data _data;
};


//! \brief Projects a grid \a original_grid by taking the dimensions corresponding to \a indices.
Grid project_down(const Grid& original_grid, const Vector<uint>& indices);

} // namespace Ariadne

#endif /* ARIADNE_GRID_H */

