#pragma once
#include <cstdio>
#include <cstdlib>

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

#define STARASSERT(expr, msg)                                                                                                                                                                                                                                  \
	if (!(expr)) {                                                                                                                                                                                                                                               \
		puts(msg);                                                                                                                                                                                                                                                 \
		std::abort();                                                                                                                                                                                                                                              \
	}
