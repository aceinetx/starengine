#pragma once
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>

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

#define STARASSERT(expr, ...)                                                                      \
  if (!(expr)) {                                                                                   \
    fmt::println("[star] Assertion failed {}: {}", #expr, __VA_ARGS__);                            \
    std::abort();                                                                                  \
  }

#define CALLBACK_0(func, self) std::bind(&func, self)
#define CALLBACK_1(func, self) std::bind(&func, self, std::placeholders::_1)
#define CALLBACK_2(func, self) std::bind(&func, self, std::placeholders::_1, std::placeholders::_2)
