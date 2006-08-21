/*
  libco_win32 : version 0.06 ~byuu (05/21/06)
  win32-x86 implementation of libco
*/

#define WINVER       0x0400
#define _WIN32_WINNT 0x0400
#include <windows.h>

#include "libco_win32.h"

namespace libco_win32 {
  bool     co_enabled  = false;
  int      co_stackptr = 0;
  thread_t co_stack[4096];

  void __stdcall coentry_proc(void *coentry) {
  thread_p main = (thread_p)coentry;
    main();
  }
};

void co_init() {
  if(libco_win32::co_enabled == true)return;
  libco_win32::co_enabled = true;

  ConvertThreadToFiber(0);
}

void co_term() {
/*****
//ConverFiberToThread() only exists on WinXP+

  if(libco_win32::co_enabled == false)return;
  libco_win32::co_enabled = false;

  ConvertFiberToThread();
*****/
}

thread_t co_active() {
  if(libco_win32::co_enabled == false)co_init();

  return GetCurrentFiber();
}

thread_t co_create(thread_p coentry, unsigned int heapsize) {
  if(libco_win32::co_enabled == false)co_init();

  return CreateFiber(heapsize, libco_win32::coentry_proc, (void*)coentry);
}

void co_delete(thread_t cothread) {
  DeleteFiber(cothread);
}

void co_jump(thread_t cothread) {
  SwitchToFiber(cothread);
}

void co_call(thread_t cothread) {
  libco_win32::co_stack[libco_win32::co_stackptr++] = co_active();
  co_jump(cothread);
}

void co_return() {
  co_jump(libco_win32::co_stack[--libco_win32::co_stackptr]);
}