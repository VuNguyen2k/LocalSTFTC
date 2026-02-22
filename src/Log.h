#pragma once
#include <fmt/core.h>

#include <iostream>

#define LOG(level, f, ...)                                                             \
  std::cout << fmt::format("[{}] [{}:{}] " f, level, __FILE__, __LINE__, #__VA_ARGS__) \
            << std::endl;
#define LOG_DEBUG(f, ...) LOG("DEBUG", f, #__VA_ARGS__);
#define LOG_INFO(f, ...) LOG("INFO", f, #__VA_ARGS__);
#define LOG_WARN(f, ...) LOG("WARN", f, #__VA_ARGS__);
#define LOG_ERROR(f, ...) LOG("ERROR", f, #__VA_ARGS__);