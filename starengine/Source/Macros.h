#pragma once
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>
#include <raylib.h>
#ifdef STAR_PLATFORM_SWITCH
#include <switch.h>
#endif

#define CREATE_FUNC(type)                                                                          \
  static type* create() {                                                                          \
    auto* pRet = new type();                                                                       \
    /* printf("[star] malloc %p\n", pRet); */                                                      \
    if (pRet && pRet->init()) {                                                                    \
      pRet->autorelease();                                                                         \
    } else {                                                                                       \
      delete pRet;                                                                                 \
      return nullptr;                                                                              \
    }                                                                                              \
    return pRet;                                                                                   \
  }

#define CREATE_FUNC_NO_INIT(type)                                                                  \
  static type* create() {                                                                          \
    auto* pRet = new type();                                                                       \
    /* printf("[star] malloc %p\n", pRet); */                                                      \
    if (pRet) {                                                                                    \
      pRet->autorelease();                                                                         \
    } else {                                                                                       \
      return nullptr;                                                                              \
    }                                                                                              \
    return pRet;                                                                                   \
  }

#ifdef STAR_PLATFORM_SWITCH
// assert behavior for nintendo switch
#define STARASSERT_PREPRINT()                                                                      \
  CloseWindow();                                                                                   \
  consoleInit(NULL)
#define STARASSERT_AFTERPRINT()                                                                    \
  consoleUpdate(NULL);                                                                             \
  for (;;)
#else
// assert behavior for everything else
#define STARASSERT_PREPRINT() CloseWindow()
#define STARASSERT_AFTERPRINT() std::abort()
#endif

#define STARASSERT(expr, ...)                                                                      \
  if (!(expr)) {                                                                                   \
    STARASSERT_PREPRINT();                                                                         \
    fmt::println("[star] Assertion failed {}: {}", #expr, __VA_ARGS__);                            \
    STARASSERT_AFTERPRINT();                                                                       \
  }

#define CALLBACK_0(func, self) std::bind(&func, self)
#define CALLBACK_1(func, self) std::bind(&func, self, std::placeholders::_1)
#define CALLBACK_2(func, self) std::bind(&func, self, std::placeholders::_1, std::placeholders::_2)
