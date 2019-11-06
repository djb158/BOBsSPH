/*----------------------------------------------------------------------------|
|                                                                             |
|   Copyright (c) 2015,2016 David Brown                                       |
|                                                                             |
|   This file is part of BOBsSPH                                              |
|                                                                             |
|   BOBsSPH is free software: you can redistribute it and/or modify           |
|   it under the terms of the GNU General Public License as published by      |
|   the Free Software Foundation, either version 3 of the License, or         |
|   (at your option) any later version.                                       |
|                                                                             |
|   BOBsSPH is distributed in the hope that it will be useful,                |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of            |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             |
|   GNU General Public License for more details.                              |
|                                                                             |
|   You should have received a copy of the GNU General Public License         |
|   along with BOBsSPH.  If not, see <http://www.gnu.org/licenses/>.          |
|                                                                             |
\*---------------------------------------------------------------------------*/

#ifndef BOBSSPH_NUMERIC_CONSTANTS_H
#define BOBSSPH_NUMERIC_CONSTANTS_H

#define PI     (3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679)
#define SQRTPI (1.7724538509055160272981674833411451827975494561223871282138077898529112845910321813749506567385446654)
#define PI3o2  (5.56832799683170787119)
#define FOUR_PI   (4.0*M_PI)
#define EPSILON_FLOAT             (1.0E-4)
#define EPSILON_DOUBLE            (1.0E-7)
#define EPSILON_LONG_DOUBLE       (1.0E-10)
#define EPSILON_LONG_LONG_DOUBLE  (1.0E-20)
#define LARGE_NEGATIVE_INT     -999999999
#define LARGE_POSITIVE_INT      999999999
#define LARGE_NEGATIVE_DOUBLE  -9999999999.0
#define LARGE_POSITIVE_DOUBLE   9999999999.0
#define LARGE_NEGATIVE_FLOAT  -9999999999.0
#define LARGE_POSITIVE_FLOAT   9999999999.0
#define LARGE_PRIME             15485863
#define ONE_QUARTER             (1.0/4.0)
#define ONE_THIRD               (1.0/3.0)
#define ONE_HALF                (1.0/2.0)
#define THREEOVER2              (1.5)
#define KERNEL_SUPPORT          (3.0)
#define KERNEL_SUPPORT_SQUARED  (KERNEL_SUPPORT*KERNEL_SUPPORT)
#define KERNEL_SUPPORT_CUBED    (KERNEL_SUPPORT_SQUARED*KERNEL_SUPPORT)

#endif /* BOBSSPH_NUMERIC_CONSTANTS_H */
