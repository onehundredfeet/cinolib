/********************************************************************************
*  This file is part of CinoLib                                                 *
*  Copyright(C) 2019: Marco Livesu                                              *
*                                                                               *
*  The MIT License                                                              *
*                                                                               *
*  Permission is hereby granted, free of charge, to any person obtaining a      *
*  copy of this software and associated documentation files (the "Software"),   *
*  to deal in the Software without restriction, including without limitation    *
*  the rights to use, copy, modify, merge, publish, distribute, sublicense,     *
*  and/or sell copies of the Software, and to permit persons to whom the        *
*  Software is furnished to do so, subject to the following conditions:         *
*                                                                               *
*  The above copyright notice and this permission notice shall be included in   *
*  all copies or substantial portions of the Software.                          *
*                                                                               *
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   *
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     *
*  FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE *
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       *
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      *
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS *
*  IN THE SOFTWARE.                                                             *
*                                                                               *
*  Author(s):                                                                   *
*                                                                               *
*     Marco Livesu (marco.livesu@gmail.com)                                     *
*     http://pers.ge.imati.cnr.it/livesu/                                       *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*********************************************************************************/
#ifndef CINO_SPATIAL_DATA_STRUCTURE_ITEM_H
#define CINO_SPATIAL_DATA_STRUCTURE_ITEM_H

/* This interface must be implemented by any item that populates a spatial data structure
 * (e.g. Octree, BSP, AABB Tree, ...). These primitives are necessary to implement both the
 * construction of the hierarchical space subdivision, and the various queries the data
 * structure may offer (e.g. ray intersection, nearest neighbor, contains, ...)
*/
namespace cinolib
{
    typedef enum
    {
        POINT,
        SEGMENT,
        TRIANGLE,
        TETRAHEDRON,
    }
    ItemType;

    class Bbox;  // axis aligned bounding box
    template<typename T> class vec3;

    class SpatialDataStructureItem
    {
        public:

            explicit SpatialDataStructureItem() {}
            virtual ~SpatialDataStructureItem() {}

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            virtual ItemType item_type() const = 0;

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            virtual Bbox aabb() const = 0;

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            // given a point in space P, finds the point in the item that is closest to P
            virtual vec3<double> point_closest_to(const vec3<double> & p) const = 0;

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            double dist     (const vec3<double> & p) const { return p.dist(point_closest_to(p));         }
            double dist_sqrd(const vec3<double> & p) const { return p.dist_squared(point_closest_to(p)); }

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            void barycentric_coordinates(const vec3<double> & p, double bc[]) const = 0;

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            // should I use an epsilon thresold here? Will see...
            bool contains(const vec3<double> & p) const { return dist_sqrd(p)==0; }

            //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

            virtual bool intersects_ray    (const vec3<double> & p, const vec3<double> & dir, double & t, vec3<double> & pos) const = 0;
            //virtual bool intersects_line   (const vec3<double> & p, const vec3<double> & dir, double & t, vec3<double> & pos) const = 0;
            //virtual bool intersects_segment(const vec3<double> & a, const vec3<double> & b,   double & t, vec3<double> & pos) const = 0;
            //virtual bool intersects_sphere (const vec3<double> & p, const double r, vec3<double> & pos) = 0;
    };
}

#endif // CINO_SPATIAL_DATA_STRUCTURE_ITEM_H
