/******************************** -*- C -*- ****************************
 *
 *	Byte Code interpreter declarations.
 *
 *
 ***********************************************************************/

/***********************************************************************
 *
 * Copyright 1988,89,90,91,92,94,95,99,2000,2001,2002
 * Free Software Foundation, Inc.
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


#ifndef GST_INTERP_H
#define GST_INTERP_H

/* The number of available process priorities */
#define NUM_PRIORITIES		 9
#define USER_SCHEDULING_PRIORITY 4

/* Ordering of file operations must match that used in
   FileStream.st */
enum
{
  PRIM_OPEN_FILE,               /* open:mode: */
  PRIM_CLOSE_FILE,              /* no args */
  PRIM_PUT_CHARS,               /* data:from:to: */
  PRIM_GET_CHARS,               /* data:from:to: */
  PRIM_FSEEK_SET,               /* position: */
  PRIM_FTELL,                   /* no args */
  PRIM_FEOF,                    /* no args */
  PRIM_OPEN_PIPE,               /* open:mode: */
  PRIM_FSEEK_CUR,               /* skip: */
  PRIM_FSIZE,                   /* no args */
  PRIM_FTRUNCATE,               /* no args */
  PRIM_FILEIN,                  /* no args */
  PRIM_FILEIN_AT,               /* line:file:charPos: */
  PRIM_SYNC_POLL,               /* read/write/exception */
  PRIM_ASYNC_POLL,              /* operation:semaphore: */
  PRIM_IS_PIPE,                 /* no args */
  PRIM_MK_TEMP                  /* base: */
};

/* These macros are used to quickly compute the number of words needed
   for a context with a maximum allowable stack depth of DEPTH.  */
#define FIXED_CTX_SIZE	(sizeof(struct gst_method_context) / sizeof(long) - 1)
#define CTX_SIZE(depth) (((depth) << DEPTH_SCALE) + FIXED_CTX_SIZE)

#define DUMMY_NATIVE_IP FROM_INT(0)

/* The structure of execution context objects. */
typedef struct gst_context_part
{
  OBJ_HEADER;
  OOP parentContext;
  OOP native_ip;		/* used by JIT */
  OOP ipOffset;			/* an integer byte index into method */
  OOP spOffset;			/* an integer index into cur context
				   stack */
  OOP receiver;			/* the receiver OOP */
  OOP method;			/* the method that we're executing */
  OOP x;			/* depends on the subclass */
  OOP contextStack[1];
}
 *gst_context_part;

typedef struct gst_method_context
{
  OBJ_HEADER;
  OOP parentContext;
  OOP native_ip;		/* used by JIT */
  OOP ipOffset;			/* an integer byte index into method */
  OOP spOffset;			/* an integer index into cur context
				   stack */
  OOP receiver;			/* the receiver OOP */
  OOP method;			/* the method that we're executing */
  long flags;			/* must be an int to distinguish
				   gst_compiled_block/gst_method_context 
				 */
  OOP contextStack[1];
}
 *gst_method_context;

/* MCF stands for MethodContext Flag.  */

/* This is always set so that Smalltalk sees the flags member as
   a SmallInteger.  BlockContexts store the outer context there,
   so it is never a SmallInteger.  */
#define MCF_IS_METHOD_CONTEXT         1

/* Answer whether this context must be skipped when doing a local
   method return.  Contexts are marked this way when an exception
   occurs or if there is a non-local method return and there are
   active #ensure: calls.  */
#define MCF_IS_DISABLED_CONTEXT       2

/* Answer whether this context must not be discarded upon a non-local
   method return.  Contexts evaluating #ensure: and/or #ifCurtailed:
   are marked this way.  */
#define MCF_IS_UNWIND_CONTEXT         4

/* Answer whether execution started from this context (this kind
   of MethodContext is used to mark call-ins from C to Smalltalk
   and is placed on top of the context that was executing at the
   time of the call-in, and is the parent of the called-in method). */
#define MCF_IS_EXECUTION_ENVIRONMENT  8


typedef struct gst_block_context
{
  OBJ_HEADER;
  OOP parentContext;
  OOP native_ip;		/* used by JIT */
  OOP ipOffset;			/* an integer byte index into method */
  OOP spOffset;			/* an integer index into cur context
				   stack */
  OOP receiver;			/* the receiver OOP */
  OOP method;			/* the method that we're executing */
  OOP outerContext;		/* the parent gst_block_context or
				   gst_method_context */
  OOP contextStack[1];
}
 *gst_block_context;

/* The structure of various objects related to the process system. */
typedef struct gst_semaphore
{
  OBJ_HEADER;
  OOP firstLink;
  OOP lastLink;
  OOP signals;
  OOP name;
}
 *gst_semaphore;

#define PROCESS_HEADER \
  OBJ_HEADER; \
  OOP nextLink; \
  OOP suspendedContext; \
  OOP priority; \
  OOP myList; \
  OOP name; \
  OOP unwindPoints; \
  OOP interrupts; \
  OOP interruptLock

typedef struct gst_process
{
  PROCESS_HEADER;
}
 *gst_process;

typedef struct gst_callin_process
{
  PROCESS_HEADER;
  OOP returnedValue;
}
 *gst_callin_process;

typedef struct gst_processor_scheduler
{
  OBJ_HEADER;
  OOP processLists;
  OOP activeProcess;
  OOP idleTasks;
  OOP processTimeslice;
  OOP gcSemaphore;
  OOP gcArray;
}
 *gst_processor_scheduler;

/* Some performance counters from the interpreter: these
   count the number of special returns. */
extern unsigned long _gst_literal_returns, _gst_inst_var_returns,
  _gst_self_returns;

/* The number of primitives executed. */
extern unsigned long _gst_primitives_executed;

/* The number of bytecodes executed. */
extern unsigned long _gst_bytecode_counter;

/* The number of method cache misses */
extern unsigned long _gst_cache_misses;

/* The number of cache lookups - either hits or misses */
extern unsigned long _gst_sample_counter;

/* If this is true, for each byte code that is executed, we print on
   stdout the byte index within the current gst_compiled_method and a
   decoded interpretation of the byte code. */
extern mst_Boolean _gst_execution_tracing;

/* When this is true, and an interrupt occurs (such as SIGSEGV),
   Smalltalk will terminate itself by making a core dump (normally it
   produces a backtrace). */
extern mst_Boolean _gst_make_core_file;

/* When true, this indicates that there is no top level loop for
   control to return to, so it causes the system to exit. */
extern mst_Boolean _gst_non_interactive;

/* The OOP for a gst_compiled_method or gst_compiled_block that is the
   currently executing method. */
extern OOP _gst_this_method;

/* Physical address of the base of the method temporary variables.
   Typically a small number of bytes (multiple of 4 since it points to
   OOPs) lower than sp. */
extern OOP *_gst_temporaries;

/* Physical address of the base of the method literals. */
extern OOP *_gst_literals;

/* An OOP that is the current receiver of the current message. */
extern OOP _gst_self;

/* A gst_block_context or gst_method_context that indicates the
   context that the interpreter is currently running in. */
extern OOP _gst_this_context_oop;

/* The type used to hold the instruction pointer.  For the JIT, this
   is an offset from a location which is deemed the `base' of
   native-compiled methods (because this way it will fit in a
   SmallInteger and can be stored in the returnIP field of the context
   objects); for the interpreter, this is the physical address of the
   next executed bytecode (note: the global is usually synchronized at
   sequence points only). */
#ifdef USE_JIT_TRANSLATION
typedef int ip_type;
extern char *native_ip;
#else /* plain bytecode interpreter */
typedef gst_uchar *ip_type;
#endif
#define ip			_gst_ip

extern ip_type ip;

/* Set to true when some special action must be done at the next
   sequence point. */
extern volatile mst_Boolean _gst_except_flag;

/* Create a new Process on the top of the stack, which is specially
   marked so that it stops the interpreter's execution.  This kind
   of MethodContext is used to mark call-ins from C to Smalltalk
   and is the parent of the called-in method.  Return the Process.  */
extern OOP _gst_prepare_execution_environment (void);

/* Sends SELECTOR (which should be a Symbol, otherwise _gst_nil_oop is
   returned) to RECEIVER.  The message arguments should also be OOPs
   (otherwise, an access violation exception is pretty likely) and are
   passed in an array ARGS of size NARGS.  The value returned from the
   method is passed back as an OOP to the C program as the result of
   the function, or _gst_nil_oop if the number of arguments is wrong.  */
extern OOP _gst_nvmsg_send (OOP receiver,
			    OOP selector,
			    OOP *args,
			    int nArgs);

/* Start the interpreter, and go on until we terminate PROCESSOOP.  */
extern OOP _gst_interpret (OOP processOOP);

/* Internal function for SEND_MESSAGE and for sends to super; send
   SENDSELECTOR, with SENDARGS arguments, to RECEIVER.  Start looking
   for the method in METHOD_CLASS. 

   On entry to this routine, the stack should have the receiver and
   the arguments pushed on the stack.  We need to get a new context,
   setup things like the IP, SP, and Temporary pointers, and then
   return.  Note that this routine DOES NOT invoke the interpreter; it
   merely sets up a new context so that calling (or, more typically,
   returning to) the interpreter will operate properly.  This kind of
   sending is for normal messages only.  Things like sending a "value"
   message to a block context are handled by primitives which do
   similar things, but they use information from gst_block_closure
   objects that we don't have available (nor need) here.  */
extern void _gst_send_message_internal (OOP sendSelector,
			      int sendArgs,
			      OOP receiver,
			      OOP method_class);

/* Prepare the data structures held by the interpreter. */
extern void _gst_init_interpreter (void);

/* Reset the fast allocator for context objects, telling it that
   all contexts living there have been tenured and thus the space
   can be reused.  */
extern void _gst_empty_context_pool (void);

/* Signal SEMAPHOREOOP so that one of the processes waiting on that
   semaphore is waken up.  Since a Smalltalk call-in is not an atomic
   operation, the correct way to signal a semaphore is not to send
   #signal to the object but, rather, to use this function.  The
   signal request will be processed as soon as the next sequence point
   is reached. */
extern void _gst_async_signal (OOP semaphoreOOP);

/* Signal SEMAPHOREOOP so that one of the processes waiting on that
   semaphore is waken up, and remove it from the registry.  Since a
   Smalltalk call-in is not an atomic operation, the correct way to
   signal a semaphore is not to send #signal to the object but,
   rather, to use this function.  The signal request will be processed
   as soon as the next sequence point is reached. */
extern void _gst_async_signal_and_unregister (OOP semaphoreOOP);

/* Invalidate all the cached CompiledMethod lookups.  This does NOT
   include inline caches when the JIT compiler is active.  */
extern void _gst_invalidate_method_cache (void);

/* Show a backtrace of the current state of the stack of execution
   contexts.  */
extern void _gst_show_backtrace (void);

/* Trap the signals that we care about, basically SIGBUS and
   SIGSEGV. */
extern void _gst_init_signals (void);

/* Store the context of the VM registers into the currently executing
   contexts.  Since the contexts store relative addresses, these are
   valid across GCs and we can count on them and on the OOPs (which do
   not move) to adjust the interior pointers that the VM uses.  Note
   that normally fields such as SP or IP are not valid for the
   currently executing contexts (they are only used after a message
   send) so we need a special function to ensure that even that
   context has the information saved in it.  */
extern void _gst_fixup_object_pointers (void);

/* Complementary to _gst_fixup_object_pointers, this function picks
   the relative addresses stored in the current context and uses
   them to adjust the VM registers after the heap is compacted or
   grown. */
extern void _gst_restore_object_pointers (void);

/* This runs before every evaluation (_gst_execute_statements) and
   before GC turned on.  It creates an initial process if no process
   is ready to run or if no process has been created yet. */
extern void _gst_init_process_system (void);

/* These function mark or copy all the objects that the interpreter keeps in
   the root set.  These are the semaphores that are held to be
   signaled by an asynchronous event (note that they *are* in the root
   set because they could be the only way from which we can get to the
   suspended process!), the semaphores that are queued to be signaled
   at the next sequence point (_gst_async_signals queues them) and the
   currently executing context.  Everything else is supposedly
   reachable from the current context (including the current method,
   the receiver, the receiver class even if it does not live in a
   namespace, and all the context on the execution stack) or from
   Processor (including the current process and the other active
   processes).  Processor itself is reachable from the Smalltalk
   dictionary.  */
extern void _gst_mark_processor_registers (void);
extern void _gst_copy_processor_registers (void);

/* Print the current state of the lists of ready to run processes for
   each priority, for debugging purposes. */
extern void _gst_print_process_state (void);

/* Sanity check the process lists that the sole instance of ProcessorScheduler
   holds.  */
extern void _gst_check_process_state (void);

/* Print the objects currently on the stack, for debugging
   purposes. */
extern void _gst_show_stack_contents (void);

/* Called after the mark phase, but before the sweep phase, so that if
   a method cache entry is not valid anymore it is cleared.  This is
   because in the JIT case a method cache entry is invalidated not
   only if the related method does not exist anymore (and this is done
   by the Smalltalk implementation of the MethodDictionary class) but
   also if the translation to native code for the method is garbage
   collected.  In particular, this function is called *after* the
   unused method translations are marked as such, and *before* they
   are actually freed. */
extern void _gst_validate_method_cache_entries (void);

/* Terminate execution of the given PROCESSOOP.  */
extern void _gst_terminate_process (OOP processOOP);

/* Similar to _gst_send_message_internal, but forces the specified
   CompiledMethod to be sent.  If it is not valid for the current
   receiver, well, you are looking for trouble and well deserve it.
   The number of arguments is looked in METHODOOP.  */
extern void _gst_send_method (OOP methodOOP);

/* This functions accepts an OOP for a Semaphore object and puts the
   current process to sleep, unless the semaphore has excess signals
   on it.  Since a Smalltalk call-in is not an atomic operation, the
   correct way to signal a semaphore is not to send the wait method to
   the object but, rather, to use _gst_sync_wait.  The `sync' in the
   name of this function distinguishes it from _gst_async_signal, in
   that it cannot be called from within a signal handler. */
extern void _gst_sync_wait (OOP semaphoreOOP);

/************************************************* PRIMITIVES ****************/

/* The type for a routine providing the definition for one or more
   primitive methods in the GNU Smalltalk system.  They normally
   remove the arguments to the primitive methods from the stack, but
   if the primitive fails, the arguments are put back onto the stack
   and the routine returns true (-1 for the JIT), indicating failure
   to invoke the primitive.  Such a function must execute a primitive,
   aided in the choice of which by the user-defined parameter ID,
   popping NUMARGS methods off the stack if they succeed.  */
typedef long (*primitive_func) (int primitive, 
				volatile int numArgs);

/* Table of primitives, including a primitive and its attributes. */
typedef struct prim_table_entry
{
  char *name;
  long attributes;
  primitive_func func;
  int id;
}
prim_table_entry;

#define PRIM_SUCCEED			0x0001
#define PRIM_FAIL			0x0002
#define PRIM_RELOAD_IP			0x0004
#define PRIM_OUTCOMES			0x0007
#define PRIM_CACHE_NEW_IP		0x0008
#define PRIM_INLINED			0x0010
#define PRIM_CHECK_INTERRUPT		0x0020
#define PRIM_RETURN_SMALL_INTEGER	0x0100	/* 31 or 63 bits */
#define PRIM_RETURN_SMALL_SMALLINTEGER	0x0300	/* 30 or 62 bits */

/* This is the bridge to the primitive operations in the GNU Smalltalk
   system.  This function invokes the proper primitive_func with the
   correct id and the same NUMARGS and METHODOOP with which it was
   invoked.  */
extern long _gst_execute_primitive_operation (int primitive,
					      volatile int numArgs);

/* This can be used to obtain information on a particular primitive
   operations in the GNU Smalltalk system.  */
extern prim_table_entry * _gst_get_primitive_attributes (int primitive) ATTRIBUTE_PURE;

/* Initialize the table of primitives. */
extern void _gst_init_primitives ();

#endif /* GST_INTERP_H */
