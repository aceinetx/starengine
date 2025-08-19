#pragma once
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>

#define CREATE_FUNC(type)                                                                                                                                                                                                                                      \
	static type* create() {                                                                                                                                                                                                                                      \
		auto* pRet = new type();                                                                                                                                                                                                                                   \
		printf("malloc %p\n", pRet);                                                                                                                                                                                                                               \
		if (pRet && pRet->init()) {                                                                                                                                                                                                                                \
			pRet->autorelease();                                                                                                                                                                                                                                     \
		} else {                                                                                                                                                                                                                                                   \
			delete pRet;                                                                                                                                                                                                                                             \
			return nullptr;                                                                                                                                                                                                                                          \
		}                                                                                                                                                                                                                                                          \
		return pRet;                                                                                                                                                                                                                                               \
	}

#define STARASSERT(expr, ...)                                                                                                                                                                                                                                  \
	if (!(expr)) {                                                                                                                                                                                                                                               \
		fmt::println(__VA_ARGS__);                                                                                                                                                                                                                                 \
		std::abort();                                                                                                                                                                                                                                              \
	}
