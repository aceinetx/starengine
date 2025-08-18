#pragma once

#define CREATE_FUNC(type)                                                                                                                                                                                                                                      \
	static type* create() {                                                                                                                                                                                                                                      \
		auto* pRet = new type();                                                                                                                                                                                                                                   \
		if (!pRet->init())                                                                                                                                                                                                                                         \
			return nullptr;                                                                                                                                                                                                                                          \
		return pRet;                                                                                                                                                                                                                                               \
	}
