#pragma once
#include <raymath.h>

namespace star {
namespace ease {
#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

inline static constexpr float easeIn(float time, float rate) {
  return powf(time, rate);
}
inline static constexpr float easeOut(float time, float rate) {
  return powf(time, 1 / rate);
}
inline static constexpr float easeInOut(float time, float rate) {
  time *= 2;
  if (time < 1) {
    return 0.5f * powf(time, rate);
  } else {
    return (1.0f - 0.5f * powf(2 - time, rate));
  }
}

inline static constexpr float quadraticIn(float time) {
  return powf(time, 2);
}
inline static constexpr float quadraticOut(float time) {
  return -time * (time - 2);
}
inline static constexpr float quadraticInOut(float time) {

  float resultTime = time;
  time = time * 2;
  if (time < 1) {
    resultTime = time * time * 0.5f;
  } else {
    --time;
    resultTime = -0.5f * (time * (time - 2) - 1);
  }
  return resultTime;
}

inline static constexpr float sineEaseIn(float time) {
  return -1 * cosf(time * (float)M_PI_2) + 1;
}
inline static constexpr float sineEaseOut(float time) {
  return sinf(time * (float)M_PI_2);
}
inline static constexpr float sineEaseInOut(float time) {
  return -0.5f * (cosf((float)M_PI * time) - 1);
}

inline static constexpr float quadEaseIn(float time) {
  return time * time;
}
inline static constexpr float quadEaseOut(float time) {
  return -1 * time * (time - 2);
}
inline static constexpr float quadEaseInOut(float time) {
  time = time * 2;
  if (time < 1)
    return 0.5f * time * time;
  --time;
  return -0.5f * (time * (time - 2) - 1);
}

inline static constexpr float cubicEaseIn(float time) {
  return time * time * time;
}
inline static constexpr float cubicEaseOut(float time) {
  time -= 1;
  return (time * time * time + 1);
}
inline static constexpr float cubicEaseInOut(float time) {
  time = time * 2;
  if (time < 1)
    return 0.5f * time * time * time;
  time -= 2;
  return 0.5f * (time * time * time + 2);
}

inline static constexpr float quartEaseIn(float time) {
  return time * time * time * time;
}
inline static constexpr float quartEaseOut(float time) {
  time -= 1;
  return -(time * time * time * time - 1);
}
inline static constexpr float quartEaseInOut(float time) {
  time = time * 2;
  if (time < 1)
    return 0.5f * time * time * time * time;
  time -= 2;
  return -0.5f * (time * time * time * time - 2);
}

inline static constexpr float quintEaseIn(float time) {
  return time * time * time * time * time;
}
inline static constexpr float quintEaseOut(float time) {
  time -= 1;
  return (time * time * time * time * time + 1);
}
inline static constexpr float quintEaseInOut(float time) {
  time = time * 2;
  if (time < 1)
    return 0.5f * time * time * time * time * time;
  time -= 2;
  return 0.5f * (time * time * time * time * time + 2);
}

inline static constexpr float expoEaseIn(float time) {
  return time == 0 ? 0 : powf(2, 10 * (time / 1 - 1)) - 1 * 0.001f;
}
inline static constexpr float expoEaseOut(float time) {
  return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1);
}
inline static constexpr float expoEaseInOut(float time) {
  if (time == 0 || time == 1)
    return time;

  if (time < 0.5f)
    return 0.5f * powf(2, 10 * (time * 2 - 1));

  return 0.5f * (-powf(2, -10 * (time * 2 - 1)) + 2);
}

inline static constexpr float circEaseIn(float time) {
  return -1 * (sqrt(1 - time * time) - 1);
}
inline static constexpr float circEaseOut(float time) {
  time = time - 1;
  return sqrt(1 - time * time);
}
inline static constexpr float circEaseInOut(float time) {
  time = time * 2;
  if (time < 1)
    return -0.5f * (sqrt(1 - time * time) - 1);
  time -= 2;
  return 0.5f * (sqrt(1 - time * time) + 1);
}

inline static constexpr float elasticEaseIn(float time, float period) {
  float newT = 0;
  if (time == 0 || time == 1) {
    newT = time;
  } else {
    float s = period / 4;
    time = time - 1;
    newT = -powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / period);
  }

  return newT;
}
inline static constexpr float elasticEaseOut(float time, float period) {
  float newT = 0;
  if (time == 0 || time == 1) {
    newT = time;
  } else {
    float s = period / 4;
    newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) + 1;
  }

  return newT;
}
inline static constexpr float elasticEaseInOut(float time, float period) {

  float newT = 0;
  if (time == 0 || time == 1) {
    newT = time;
  } else {
    time = time * 2;
    if (!period) {
      period = 0.3f * 1.5f;
    }

    float s = period / 4;

    time = time - 1;
    if (time < 0) {
      newT = -0.5f * powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / period);
    } else {
      newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) * 0.5f + 1;
    }
  }
  return newT;
}

inline static constexpr float backEaseIn(float time) {
  float overshoot = 1.70158f;
  return time * time * ((overshoot + 1) * time - overshoot);
}
inline static constexpr float backEaseOut(float time) {
  float overshoot = 1.70158f;

  time = time - 1;
  return time * time * ((overshoot + 1) * time + overshoot) + 1;
}
inline static constexpr float backEaseInOut(float time) {
  float overshoot = 1.70158f * 1.525f;

  time = time * 2;
  if (time < 1) {
    return (time * time * ((overshoot + 1) * time - overshoot)) / 2;
  } else {
    time = time - 2;
    return (time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1;
  }
}

inline static constexpr float bounceTime(float time) {
  if (time < 1 / 2.75f) {
    return 7.5625f * time * time;
  } else if (time < 2 / 2.75f) {
    time -= 1.5f / 2.75f;
    return 7.5625f * time * time + 0.75f;
  } else if (time < 2.5f / 2.75f) {
    time -= 2.25f / 2.75f;
    return 7.5625f * time * time + 0.9375f;
  }

  time -= 2.625f / 2.75f;
  return 7.5625f * time * time + 0.984375f;
}
inline static constexpr float bounceEaseIn(float time) {
  return 1 - bounceTime(1 - time);
}
inline static constexpr float bounceEaseOut(float time) {
  return bounceTime(time);
}
inline static constexpr float bounceEaseInOut(float time) {
  float newT = 0;
  if (time < 0.5f) {
    time = time * 2;
    newT = (1 - bounceTime(1 - time)) * 0.5f;
  } else {
    newT = bounceTime(time * 2 - 1) * 0.5f + 0.5f;
  }

  return newT;
}
} // namespace ease
} // namespace star
