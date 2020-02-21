/********************************************************************************
*  This file is part of CinoLib                                                 *
*  Copyright(C) 2016: Marco Livesu                                              *
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
#ifndef CINO_EXACT_GEOMETRIC_PREDICATES
#define CINO_EXACT_GEOMETRIC_PREDICATES

#include <cinolib/geometry/vec2.h>
#include <cinolib/geometry/vec3.h>

namespace cinolib
{

/* Exact predicates to test point in segment/triangle/tetrahedron, and
 * also to test intersections between segments/triangles/tets in 2D and
 * 3D. All test are based on the popular Shewchuk's exact orient predicates.
 *
 * When present, the "strict" variable allows to restrict the search only
 * to the interior, ignoring simplices that touch at their boundary, even
 * in non conforming ways (i.e. when they do not define a valid simplicial
 * complex).
 *
 * Return values: the point_in_{segment | triangle | tet} predicates return
 * an integer flag which indicates exactly where, in the input simplex, the
 * point is located. Intersection queries return a boolean flag which indicates
 * whether the input simplices have at least one point in common (borders are
 * ignored if strict is set to true).
 *
 * Point location indicators: a point may belong to multiple sub-simplices.
 * For example, a point coincident to a triangle vertex belongs to a 0-dimensional
 * simplex (the vertex), at least two 2-dimensional simplices (its incident
 * edges), and one 2-dimensional simplex (the triangle). The integer flag points
 * to the lowest dimensional (sub) simplex that fully contains the point.
 *
 * WARNING: for degenerate elements such as zero length segments, zero area
 * triangles and zero volume tets, the lowest dimensional simplex containing
 * a point may not be unique. In these cases, only one of them will be returned.
 */

// location of intersection points for point_in_{segment | triangle | tet}
// predicates. Elements' orders are compliant with the tables in:
//
//   #include <cinolib/standard_elements_tables.h>
enum
{
    STRICTLY_OUTSIDE = 0,  // strictly outside the input simplex
    STRICTLY_INSIDE  = 1,  // strictly inside  the input simplex
    ON_VERT0         = 2,  // used for segs, tris and tets
    ON_VERT1         = 3,  // used for segs, tris and tets
    ON_VERT2         = 4,  // used for tris and tets
    ON_VERT3         = 5,  // used for tets
    ON_EDGE0         = 6,  // used for tris and tets
    ON_EDGE1         = 7,  // used for tris and tets
    ON_EDGE2         = 8,  // used for tris and tets
    ON_EDGE3         = 9,  // used for tets
    ON_EDGE4         = 10, // used for tets
    ON_EDGE5         = 11, // used for tets
    ON_FACE0         = 12, // used for tets
    ON_FACE1         = 13, // used for tets
    ON_FACE2         = 14, // used for tets
    ON_FACE3         = 15, // used for tets
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// true if the area of the triangle p0-p1-p2 is zero
CINO_INLINE
bool points_are_colinear_exact(const vec2d & p0,
                               const vec2d & p1,
                               const vec2d & p2);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// true if the area of all the orthogonal 2d projections of the triangle p0-p1-p2 is zero
CINO_INLINE
bool points_are_colinear_exact(const vec3d & p0,
                               const vec3d & p1,
                               const vec3d & p2);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// true if the volume of the tetrahedron p0-p1-p2-p3 is zero
CINO_INLINE
bool points_are_coplanar_exact(const vec3d & p0,
                               const vec3d & p1,
                               const vec3d & p2,
                               const vec3d & p3);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ON_VERT0         if p coincides with s[0]
// ON_VERT1         if p coincides with s[1]
// STRICTLY_INSIDE  if p lies in between s[0] and s[1] (not included)
// STRICTLY_OUTSIDE otherwise
CINO_INLINE
int point_in_segment_exact(const vec2d & p,
                           const vec2d  s[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ON_VERT0         if p coincides with s[0]
// ON_VERT1         if p coincides with s[1]
// STRICTLY_INSIDE  if p lies in between s[0] and s[1] (not included)
// STRICTLY_OUTSIDE otherwise
CINO_INLINE
int point_in_segment_exact(const vec3d & p,
                           const vec3d   s[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// ON_VERT0         if p coincides with t[0]
// ON_VERT1         if p coincides with t[1]
// ON_VERT2         if p coincides with t[2]
// ON_EDGE0         if p lies in between t[0] and t[1] (not included)
// ON_EDGE1         if p lies in between t[1] and t[2] (not included)
// ON_EDGE2         if p lies in between t[2] and t[0] (not included)
// STRICTLY_INSIDE  if p lies inside triangle t (borders not included)
// STRICTLY_OUTSIDE otherwise
CINO_INLINE
int point_in_triangle_exact(const vec2d & p,
                            const vec2d   t[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
int point_in_triangle_exact(const vec3d & p,
                            const vec3d   t[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
int point_in_tet_exact(const vec3d & p,
                       const vec3d   t[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool segment_segment_intersect_exact(const vec2d  s0[],
                                     const vec2d  s1[],
                                     const bool & strict);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool segment_segment_intersect_exact(const vec3d  s0[],
                                     const vec3d  s1[],
                                     const bool & strict);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool segment_triangle_intersect_exact(const vec2d s[],
                                      const vec2d t[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool segment_triangle_intersect_exact(const vec3d s[],
                                      const vec3d t[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool triangle_triangle_intersect_exact(const vec2d t0[],
                                       const vec2d t1[]);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CINO_INLINE
bool triangle_triangle_intersect_exact(const vec3d t0[],
                                       const vec3d t1[]);

}

#ifndef  CINO_STATIC_LIB
#include "exact_geometric_predicates.cpp"
#endif

#endif // CINO_INTERSECTION_EXACT_PREDICATES
