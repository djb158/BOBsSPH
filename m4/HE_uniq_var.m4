#serial 0.0.1
|-----------------------------------------------------------------------------|
|                                                                             |
|   Copyright (c) 2008 Henrik Edlund                                          |
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
#
# HE_UNIQ_VAR(VARIABLE)
# ----------------------
# Discard all but first of identical fields (run of non-whitespace characters)
# from value of variable VARIABLE by splitting value on whitespace into
# fields, then dropping duplicate fields (keeping the first field), and then
# concatenating all remaining fields with one space into a new value.
#
# This macro is useful when reducing the size of an argument list where
# precedence (added order) is important.
#
# Example:   configure.ac:  FOO="foo bar fie fie fum baz fum fie bar foo"
#                           HE_UNIQ_FIRST_VAR([FOO])
#                           ${ECHO} "<${FOO}>"
#           
#            Output:        <foo bar fie fum baz>
#
# Note/Bug:  New value will end with an extraneous space
#
# Remark:    Deleting an entire array is a gawk extension. For standard nawk,
#            for an array a, one needs to do "for (x in a) {delete a[x]};"
#            instead of "delete a;"
#
AC_DEFUN([HE_UNIQ_VAR],
[AC_REQUIRE([AC_PROG_AWK])
$1=`${AWK} '{i=0; for (j=NF; j>0; j--) if (!($j in a)) {a@<:@$j@:>@; printf("%s ", $j)}; printf("\n"); for (x in a) {delete a@<:@xj@:>@}}' << EOF
${$1}
EOF
`
])
