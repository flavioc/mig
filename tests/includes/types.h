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

#include <stdint.h>

typedef int another_int;
typedef int *int_array;

typedef struct char_struct {
  char c1;
  char c2;
  char c3;
  char c4;
} char_struct_t;

typedef struct padding_struct {
   char a;
   short b;
   int c;
   int *d;
} padding_struct_t;

typedef struct small_struct {
  char c1;
} small_struct_t;

typedef char* string_t;
typedef char string1_t[1024];
typedef string1_t string3_t;
typedef string_t string2_t;
typedef string_t string4_t;

typedef struct {
   int x;
   int arr[2 + 2][2];
   int *ptr;
} array_struct_t;

typedef struct i386_xfp_save i386_xfp_save_t;

union union_type {
   int a;
   int b;
};
typedef union union_type union_type_t;
typedef union { int a; char b; } union_type2_t;
typedef union union_type3 { int a; char b; } union_type3_t;

typedef struct {
   int x;
   union {
      int a;
      char b;
   };
} union_struct_t;

typedef enum enum_type {
	ENUM1 = 0, ENUM2 = 3
} enum_type_t;

typedef enum {
	ENUM
} enum_type2_t;

static inline int8_t int_to_int8(int n) {
  return (int8_t) n;
}

static inline int int8_to_int(int8_t n) {
  return (int) n;
}

#endif
