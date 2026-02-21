#pragma once
#include <fmt/core.h>

#include <iostream>

#define LOG(level, fmt, ...)                                                           \
  std::cout << fmt::format("[{}] [{}:{}] " fmt, level, __FILE__, __LINE__, __VA_ARG__) \
            << std::endl;
#define LOG_DEBUG(fmt, ...) LOG("DEBUG", fmt, __VA_ARG__);
#define LOG_INFO(fmt, ...) LOG("INFO", fmt, __VA_ARG__);
#define LOG_WARN(fmt, ...) LOG("WARN", fmt, __VA_ARG__);
#define LOG_ERROR(fmt, ...) LOG("ERROR", fmt, __VA_ARG__);