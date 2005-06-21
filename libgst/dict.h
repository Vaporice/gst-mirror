/******************************** -*- C -*- ****************************
 *
 *	Dictionary Support Module Definitions.
 *
 *
 ***********************************************************************/

/***********************************************************************
 *
 * Copyright 2000, 2001, 2002 Free Software Foundation, Inc.
 * Written by Steve Byrne.
 *
 * This file is part of GNU Smalltalk.
 *
 * GNU Smalltalk is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later 
 * version.
 * 
 * GNU Smalltalk is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * GNU Smalltalk; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02110-1301, USA.  
 *
 ***********************************************************************/


#ifndef GST_DICT_H
#define GST_DICT_H

/***********************************************************************
 *
 *	Below are the structural definitions for several of the important
 *	objects present in the Smalltalk system.  Their C representation
 *	corresponds exactly with their Smalltalk representation.
 *
 ***********************************************************************/

 /* Note the use of structural inheritance in C structure definitions
    here */


typedef struct gst_file_stream
{
  OBJ_HEADER;
  OOP collection;
  OOP ptr;
  OOP endPtr;
  OOP access;
  OOP file;
  OOP name;
  OOP isPipe;
  OOP writePtr;
  OOP writeEnd;
}
 *gst_file_stream;

typedef struct gst_dictionary
{
  OBJ_HEADER;
  OOP tally;			/* really, an int */

  /* Other, indexable fields that are the associations for this
     dictionary. */
}
 *gst_dictionary;

typedef struct gst_binding_dictionary
{
  OBJ_HEADER;
  OOP tally;			/* really, an int */
  OOP environment;
  OOP assoc[1];

  /* Other, indexable fields that are the associations for this
     dictionary. */
}
 *gst_binding_dictionary;

typedef struct gst_namespace
{
  OBJ_HEADER;
  OOP tally;			/* really, an int */
  OOP superspace;
  OOP name;
  OOP subspaces;
  OOP assoc[1];

  /* Other, indexable fields that are the associations for this
     dictionary. */
}
 *gst_namespace;

typedef struct gst_identity_dictionary
{
  OBJ_HEADER;
  OOP tally;			/* really, an int */
  OOP values;			/* an gst_array */
  OOP keys[1];			/* variable sized array of OOPS
				   (symbols) */
}
 *gst_identity_dictionary;


#define BEHAVIOR_HEADER \
  OBJ_HEADER; \
  OOP		superclass; \
  OOP		subClasses; \
  OOP		methodDictionary; \
  long		instanceSpec; \
  OOP		instanceVariables

typedef struct gst_behavior
{
  BEHAVIOR_HEADER;
}
 *gst_behavior;

#define CLASS_DESCRIPTION_HEADER \
  BEHAVIOR_HEADER

#define COBJECT_ANON_TYPE		FROM_INT(-1)
#define COBJECT_CHAR_TYPE		FROM_INT(0)
#define COBJECT_UNSIGNED_CHAR_TYPE	FROM_INT(1)
#define COBJECT_SHORT_TYPE	FROM_INT(2)
#define COBJECT_UNSIGNED_SHORT_TYPE FROM_INT(3)
#define COBJECT_LONG_TYPE		FROM_INT(4)
#define COBJECT_UNSIGNED_LONG_TYPE	FROM_INT(5)
#define COBJECT_FLOAT_TYPE	FROM_INT(6)
#define COBJECT_DOUBLE_TYPE	FROM_INT(7)
#define COBJECT_STRING_TYPE	FROM_INT(8)
#define COBJECT_SMALLTALK_TYPE    FROM_INT(9)
#define COBJECT_INT_TYPE		FROM_INT(10)
#define COBJECT_UNSIGNED_INT_TYPE	FROM_INT(11)

typedef struct gst_class_description
{
  CLASS_DESCRIPTION_HEADER;
}
 *gst_class_description;

typedef struct gst_association
{
  OBJ_HEADER;
  OOP key;
  OOP value;
}
 *gst_association;

typedef struct gst_variable_binding
{
  OBJ_HEADER;
  OOP key;
  OOP value;
  OOP environment;
}
 *gst_variable_binding;

typedef struct gst_floatd
{
  OBJ_HEADER;
  double value;
}
 *gst_floatd;

typedef struct gst_floate
{
  OBJ_HEADER;
  float value;
}
 *gst_floate;

typedef struct gst_floatq
{
  OBJ_HEADER;
  long double value;
}
 *gst_floatq;

typedef struct gst_message
{
  OBJ_HEADER;
  OOP selector;
  OOP args;
}
 *gst_message;

typedef struct gst_directed_message
{
  OBJ_HEADER;
  OOP selector;
  OOP args;
  OOP receiver;
}
 *gst_directed_message;

typedef struct gst_string
{
  OBJ_HEADER;
  char chars[1];
}
 *gst_string;

typedef struct gst_byte_array
{
  OBJ_HEADER;
  gst_uchar bytes[1];
}
 *gst_byte_array;


typedef struct gst_class
{
  CLASS_DESCRIPTION_HEADER;
  OOP name;
  OOP comment;
  OOP category;
  OOP environment;
  OOP classVariables;		/* dictionary of varName, storage */
  OOP sharedPools;
}
 *gst_class;

typedef struct gst_metaclass
{
  CLASS_DESCRIPTION_HEADER;
  OOP instanceClass;
}
 *gst_metaclass;

typedef struct gst_cobject
{
  OBJ_HEADER;
  OOP type;
}
 *gst_cobject;

typedef struct gst_ctype
{
  OBJ_HEADER;
  OOP cObjectType;		/* the gst_cobject subclass to use when
				   instantiating this type */
}
 *gst_ctype;


extern OOP _gst_object_class, _gst_magnitude_class, _gst_char_class,
  _gst_time_class, _gst_date_class, _gst_fraction_class,
  _gst_context_part_class, _gst_number_class, _gst_float_class,
  _gst_floatd_class, _gst_floate_class, _gst_floatq_class,
  _gst_integer_class, _gst_small_integer_class,
  _gst_object_memory_class, _gst_large_integer_class,
  _gst_large_negative_integer_class, _gst_large_zero_integer_class,
  _gst_large_positive_integer_class, _gst_association_class,
  _gst_homed_association_class, _gst_variable_binding_class,
  _gst_link_class, _gst_process_class, _gst_sym_link_class,
  _gst_callin_process_class,
  _gst_collection_class, _gst_lookup_key_class,
  _gst_sequenceable_collection_class, _gst_linked_list_class,
  _gst_semaphore_class, _gst_method_dictionary_class,
  _gst_arrayed_collection_class, _gst_array_class, _gst_string_class,
  _gst_symbol_class, _gst_byte_array_class, _gst_compiled_method_class,
  _gst_compiled_code_class, _gst_compiled_block_class,
  _gst_interval_class, _gst_ordered_collection_class,
  _gst_sorted_collection_class, _gst_bag_class,
  _gst_mapped_collection_class, _gst_set_class, _gst_dictionary_class,
  _gst_binding_dictionary_class, _gst_abstract_namespace_class,
  _gst_character_array_class, _gst_system_dictionary_class,
  _gst_namespace_class, _gst_identity_dictionary_class,
  _gst_undefined_object_class, _gst_boolean_class, _gst_false_class,
  _gst_true_class, _gst_lookup_table_class,
  _gst_processor_scheduler_class, _gst_delay_class,
  _gst_shared_queue_class, _gst_behavior_class,
  _gst_root_namespace_class, _gst_byte_stream_class,
  _gst_class_description_class, _gst_class_class, _gst_metaclass_class,
  _gst_smalltalk_dictionary, _gst_message_class,
  _gst_directed_message_class,
  _gst_method_context_class, _gst_block_context_class,
  _gst_block_closure_class, _gst_stream_class,
  _gst_positionable_stream_class, _gst_read_stream_class,
  _gst_write_stream_class, _gst_read_write_stream_class,
  _gst_file_descriptor_class, _gst_file_stream_class,
  _gst_c_object_class, _gst_c_type_class, _gst_memory_class,
  _gst_random_class, _gst_c_func_descriptor_class,
  _gst_token_stream_class, _gst_method_info_class,
  _gst_file_segment_class, _gst_c_object_type_ctype, _gst_processor_oop;

/* Creates a new instance of the Dictionary class with room for SIZE
   items. */
extern OOP _gst_dictionary_new (int size);

/* Creates a new instance of the BindingDictionary class with room for SIZE
   items.  The object has the ENVIRONMENTOOP environment (which for
   dictionary of class variables is the class that hosts the dictionary). */
extern OOP _gst_binding_dictionary_new (int size,
			        	OOP environmentOOP);

/* Gets the method dictionary associated with CLASS_OOP, and returns
   it.  If the methodDictionary associated with CLASS_OOP is nil, one
   is created and installed into that class. */
extern OOP _gst_valid_class_method_dictionary (OOP class_oop) ATTRIBUTE_PURE;

/* This returns the dictionary of class variables for CLASS_OOP */
extern OOP _gst_class_variable_dictionary (OOP class_oop) ATTRIBUTE_PURE;

/* This finds the key SYMBOL into the dictionary POOLOOP and, if any,
   in all of its super-namespaces. */
extern OOP _gst_find_shared_pool_variable (OOP poolOOP,
					   OOP symbol) ATTRIBUTE_PURE;

/* Adds the Association in ASSOCIATIONOOP to the Dictionary (or a
   subclass sharing the same representation) DICTIONARYOOP. */
extern OOP _gst_dictionary_add (OOP dictionaryOOP,
				OOP associationOOP);

/* Creates a String object starting from the NUL-terminated string
   S. */
extern OOP _gst_string_new (const char *s);

/* Look in the Smalltalk dictionary for a class whose name is in the
   Symbol CLASSNAMEOOP. */
extern OOP _gst_find_class (OOP classNameOOP) ATTRIBUTE_PURE;

/* Look for an implementation of SELECTOR (a Symbol) into CLASS_OOP's
   method dictionary or in the method dictionary of a superclass. */
extern OOP _gst_find_class_method (OOP class_oop,
				   OOP selector) ATTRIBUTE_PURE;

/* Create a new Message object for the given SELECTOR (a Symbol) and
   Array of arguments. */
extern OOP _gst_message_new_args (OOP selectorOOP,
				  OOP argsArray);

/* Create a new DirectedMessage object for the given RECEIVER,
   SELECTOR (a Symbol) and Array of arguments. */
extern OOP _gst_directed_message_new_args (OOP receiverOOP,
					   OOP selectorOOP,
					   OOP argsArray);

/* Returns the name of CLASS_OOP (a Smalltalk Class) */
extern OOP _gst_get_class_symbol (OOP class_oop) ATTRIBUTE_PURE;

/* Create and return an exact copy of OOP, which can be any kind
   of OOP.  Builtin OOPs and integers are returned unchanged,
   while for other objects this is a "shallow copy"; all the
   instance variables in the new object are the exact same ones
   that are in the original object. */
extern OOP _gst_object_copy (OOP oop);

/* Returns the array of the names of the instance variables of
   CLASS_OOP (a Smalltalk Class). */
extern OOP _gst_instance_variable_array (OOP class_oop) ATTRIBUTE_PURE;

/* Returns the array of the names of the pool dictionaries of
   CLASS_OOP (a Smalltalk Class). */
extern OOP _gst_shared_pool_dictionary (OOP class_oop) ATTRIBUTE_PURE;

/* Creates a new CObject pointing to cObjPtr, extracting the name of
   the class to be instantiated from the CType, TYPEOOP. */
extern OOP _gst_c_object_new_typed (PTR cObjPtr,
				    OOP typeOOP);

/* Allocates a new CObject by malloc-ing SIZE bytes; CLASS_OOP is the
   class to be instantiated. */
extern OOP _gst_alloc_cobject (OOP class_oop,
			       long unsigned int size);

/* Creates a new CType that when passed to _gst_c_object_new_typed
   creates an instance of COBJECTSUBCLASSOOP. */
extern OOP _gst_c_type_new (OOP cObjectSubclassOOP);

/* Creates a new String with LEN indexed instance variables. */
extern OOP _gst_new_string (int len);

/* Creates a new ByteArray containing LEN bytes starting at BYTES. */
extern OOP _gst_byte_array_new (const gst_uchar * bytes,
				int len);

/* Creates a new String containing LEN characters starting at S. */
extern OOP _gst_counted_string_new (const char *s,
				    int len);

/* Adds the key KEYOOP, associated with VALUEOOP, to the
   IdentityDictionary (or a subclass sharing the same representation)
   IDENTITYDICTIONARYOOP. */
extern OOP _gst_identity_dictionary_at_put (OOP identityDictionaryOOP,
					    OOP keyOOP,
					    OOP valueOOP);

/* Called when a dictionary becomes full, this routine replaces the
   dictionary instance that DICTIONARYOOP is pointing to with a new,
   larger dictionary, and returns this new dictionary (the object
   pointer, not the OOP). */
extern mst_Object _gst_grow_dictionary (OOP dictionaryOOP);

/* Called when an IdentityDictionary becomes full, this routine
   replaces the IdentityDictionary instance that IDENTITYDICTIONARYOOP
   is pointing to with a new, larger dictionary, and returns this new
   dictionary (the object pointer, not the OOP). */
extern gst_identity_dictionary _gst_grow_identity_dictionary (OOP identityDictionaryOOP);

/* Allocates and returns a new C (ASCIZ) string that has the same
   contents as STRINGOOP.  Even if there are embedded NULs, the
   allocated area has always a size of "stringOOP size + 1" bytes. */
extern char *_gst_to_cstring (OOP stringOOP);

/* Allocates and returns a new memory block that has the same contents
   as BYTEARRAYOOP.  Even if there are embedded NULs, the allocated
   area has always a size of "byteArrayOOP size" bytes. */
extern gst_uchar *_gst_to_byte_array (OOP byteArrayOOP);

/* Creates the kernel classes of the Smalltalk system.  Operates in two
   passes: pass1 creates the class objects, but they're not completely
   initialized.  pass2 finishes the initialization process.  The garbage
   collector can NOT run during this time. */
extern void _gst_init_dictionary (void);

/* Copies the first bytes of S into STRINGOOP (as many bytes as the
   OOP can hold). */
extern void _gst_set_oopstring (OOP stringOOP,
				const char *s);

/* Set the instance variables of the FileStream object,
   FILESTREAMOOP.  If BUFFERED is true, the variables
   inherited by Streams are set to a 1024-bytes String. */
extern void _gst_set_file_stream_file (OOP fileStreamOOP,
				       int fd,
				       OOP fileNameOOP,
				       mst_Boolean isPipe,
				       int access,
				       mst_Boolean buffered);

/* Copies the first bytes of BYTES into BYTEARRAYOOP (as many bytes as
   the OOP can hold). */
extern void _gst_set_oop_bytes (OOP byteArrayOOP,
				gst_uchar * bytes);

/* Frees the memory pointed to by the CObject, COBJOOP. */
extern void _gst_free_cobject (OOP cObjOOP);

/* Loads the contents of the global variable from the Smalltalk
   dictionary after NUMOOPS objects have been loaded from an
   image. */
extern mst_Boolean _gst_init_dictionary_on_image_load (long numOOPs);

/* Transforms a primitive name into a primitive index, looking up
   the VMPrimitives dictionary. */
extern int _gst_resolve_primitive_name (char *name);

#endif /* GST_DICT_H */
