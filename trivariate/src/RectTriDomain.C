/*
 * Copyright (C) 1998, 2000-2007, 2010, 2011, 2012, 2013 SINTEF ICT,
 * Applied Mathematics, Norway.
 *
 * Contact information: E-mail: tor.dokken@sintef.no                      
 * SINTEF ICT, Department of Applied Mathematics,                         
 * P.O. Box 124 Blindern,                                                 
 * 0314 Oslo, Norway.                                                     
 *
 * This file is part of GoTools.
 *
 * GoTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version. 
 *
 * GoTools is distributed in the hope that it will be useful,        
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with GoTools. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In accordance with Section 7(b) of the GNU Affero General Public
 * License, a covered work must retain the producer line in every data
 * file that is created or manipulated using GoTools.
 *
 * Other Usage
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the GoTools library without
 * disclosing the source code of your own applications.
 *
 * This file may be used in accordance with the terms contained in a
 * written agreement between you and SINTEF ICT. 
 */

#include <algorithm>
#include "GoTools/trivariate/RectTriDomain.h"

#ifdef __BORLANDC__
#include <cmath> // For fabs. Should be required by VC++ and GCC as well...
using std::fabs;
#endif

namespace Go {


//===========================================================================
RectTriDomain::RectTriDomain(const Array<double, 3>& corner1, 
		       const Array<double, 3>& corner2)
//===========================================================================
{
    ll_[0] = std::min(corner1[0], corner2[0]);
    ur_[0] = std::max(corner1[0], corner2[0]);
    ll_[1] = std::min(corner1[1], corner2[1]);
    ur_[1] = std::max(corner1[1], corner2[1]);
    ll_[2] = std::min(corner1[2], corner2[2]);
    ur_[2] = std::max(corner1[2], corner2[2]);
}


//===========================================================================
RectTriDomain::~RectTriDomain()
//===========================================================================
{
}


//  //===========================================================================
//  DomainType RectTriDomain::domainType() const
//  //===========================================================================
//  {
//      return RectTriDomain;
//  }


//===========================================================================
bool RectTriDomain::isInDomain(const Array<double, 3>& point, 
			    double tolerance) const
//===========================================================================
{
    if (point[0] < ll_[0] - tolerance)
	return false;
    if (point[0] > ur_[0] + tolerance)
	return false;
    if (point[1] < ll_[1] - tolerance)
	return false;
    if (point[1] > ur_[1] + tolerance)
	return false;
    if (point[2] < ll_[2] - tolerance)
	return false;
    if (point[2] > ur_[2] + tolerance)
	return false;
    return true;
}


//===========================================================================
int RectTriDomain::isInDomain2(const Array<double, 3>& point, 
			    double tolerance) const
//===========================================================================
{
    if (point[0] < ll_[0] - tolerance)
	return 0;
    if (point[0] > ur_[0] + tolerance)
	return 0;
    if (point[1] < ll_[1] - tolerance)
	return 0;
    if (point[1] > ur_[1] + tolerance)
	return 0;
    if (point[2] < ll_[2] - tolerance)
	return 0;
    if (point[2] > ur_[2] + tolerance)
	return 0;
    if (point[0] < ll_[0] + tolerance)
	return 2;
    if (point[0] > ur_[0] - tolerance)
	return 2;
    if (point[1] < ll_[1] + tolerance)
	return 2;
    if (point[1] > ur_[1] - tolerance)
	return 2;
    if (point[2] < ll_[2] + tolerance)
	return 2;
    if (point[2] > ur_[2] - tolerance)
	return 2;
    return 1;
}


//===========================================================================
bool RectTriDomain::isOnBoundary(const Array<double, 3>& point, 
			      double tolerance) const
//===========================================================================
{
    // Being on the boundary implies being in the domain
    if (!isInDomain(point, tolerance))
	return false;

    if (point[0] < ll_[0] + tolerance)
	return true;
    if (point[0] > ur_[0] - tolerance)
	return true;
    if (point[1] < ll_[1] + tolerance)
	return true;
    if (point[1] > ur_[1] - tolerance)
	return true;
    if (point[2] < ll_[2] + tolerance)
	return true;
    if (point[2] > ur_[2] - tolerance)
	return true;
    return false;
}



//===========================================================================
void RectTriDomain::closestInDomain(const Array<double, 3>& point,
				 Array<double, 3>& clo_pt,
				 double tolerance) const
//===========================================================================
{
    clo_pt = point;
    if (clo_pt[0] < ll_[0] - tolerance)
	clo_pt[0] = ll_[0];
    if (clo_pt[0] > ur_[0] + tolerance)
	clo_pt[0] = ur_[0];
    if (clo_pt[1] < ll_[1] - tolerance)
	clo_pt[1] = ll_[1];
    if (clo_pt[1] > ur_[1] + tolerance)
	clo_pt[1] = ur_[1];
    if (clo_pt[2] < ll_[2] - tolerance)
	clo_pt[2] = ll_[2];
    if (clo_pt[2] > ur_[2] + tolerance)
	clo_pt[2] = ur_[2];
}


//===========================================================================
void RectTriDomain::closestOnBoundary(const Array<double, 3>& point,
				   Array<double, 3>& clo_bd_pt,
				   double tolerance) const
//===========================================================================
{
    clo_bd_pt = point;
    double dist1 = fabs(point[0] - ll_[0]);
    double dist2 = fabs(point[0] - ur_[0]);
    double dist3 = fabs(point[1] - ll_[1]);
    double dist4 = fabs(point[1] - ur_[1]);
    double dist5 = fabs(point[2] - ll_[2]);
    double dist6 = fabs(point[2] - ur_[2]);
    if (std::min(dist1, dist2) < std::min(dist3, dist4) &&
	std::min(dist1, dist2) < std::min(dist5, dist6)) {
	if (dist1 < dist2) {
	    clo_bd_pt[0] = ll_[0];
	} else {
	    clo_bd_pt[0] = ur_[0];
	}
    } else if (std::min(dist3, dist4) < std::min(dist5, dist6)) {
	if (dist3 < dist4) {
	    clo_bd_pt[1] = ll_[1];
	} else {
	    clo_bd_pt[1] = ur_[1];
	}
    } else {
	if (dist5 < dist6) {
	    clo_bd_pt[2] = ll_[2];
	} else {
	    clo_bd_pt[2] = ur_[2];
	}
    }

    return;
}

//===========================================================================
void RectTriDomain::addUnionWith(const RectTriDomain& rd)
//===========================================================================
{
    if (rd.ll_[0] < ll_[0])
	ll_[0] = rd.ll_[0];
    if (rd.ll_[1] < ll_[1])
	ll_[1] = rd.ll_[1];
    if (rd.ll_[2] < ll_[2])
	ll_[2] = rd.ll_[2];
    if (rd.ur_[0] > ur_[0])
	ur_[0] = rd.ur_[0];
    if (rd.ur_[1] > ur_[1])
	ur_[1] = rd.ur_[1];
    if (rd.ur_[2] > ur_[2])
	ur_[2] = rd.ur_[2];
}

//===========================================================================
void RectTriDomain::intersectWith(const RectTriDomain& rd)
//===========================================================================
{
    ll_[0] = std::max(rd.ll_[0], ll_[0]);
    ll_[1] = std::max(rd.ll_[1], ll_[1]);
    ll_[2] = std::max(rd.ll_[2], ll_[2]);
    ur_[0] = std::min(rd.ur_[0], ur_[0]);
    ur_[1] = std::min(rd.ur_[1], ur_[1]);
    ur_[2] = std::min(rd.ur_[2], ur_[2]);
}

//===========================================================================
  bool RectTriDomain::overlap(const RectTriDomain& rd, double tol)
//===========================================================================
{
  if (ll_[0] > rd.ur_[0]+tol)
    return false;
  if (ur_[0] < rd.ll_[0]-tol)
    return false;
  if (ll_[1] > rd.ur_[1]+tol)
    return false;
  if (ur_[1] < rd.ll_[1]-tol)
    return false;
  if (ll_[2] > rd.ur_[2]+tol)
    return false;
  if (ur_[2] < rd.ll_[2]-tol)
    return false;
  return true;
}
} // namespace Go
