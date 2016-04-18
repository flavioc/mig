/*
   Copyright (C) 2016 Free Software Foundation, Inc.

   This file is part of GNU MIG.

   GNU MIG is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   GNU MIG is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GNU MIG.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef TEST_TYPES_H
#define TEST_TYPES_H

typedef int another_int;

typedef struct char_struct {
  char c1;
  char c2;
  char c3;
  char c4;
} char_struct_t;

typedef char* string_t;

static inline int8_t int_to_int8(int n) {
  return (int8_t) n;
}

static inline int int8_to_int(int8_t n) {
  return (int) n;
}

#endif
