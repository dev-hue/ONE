/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file     Reader.h
 * @brief    This file contains Reader structure
 * @ingroup  COM_AI_RUNTIME
 */

#ifndef __NNFW_MISC_KERNEL_READER_H__
#define __NNFW_MISC_KERNEL_READER_H__

#include <cstdint>

namespace nnfw
{
namespace misc
{
namespace kernel
{

/**
 * @brief Structure to Reader
 */
template <typename T> struct Reader
{
  /**
   * @brief Destroy the Reader object as default
   */
  virtual ~Reader() = default;

  /**
   * @brief Get the value used by four indexes
   * @param[in] nth The kernel index
   * @param[in] ch The channel index
   * @param[in] row The row index
   * @param[in] col The column index
   * @return The value at the offset
   */
  virtual T at(uint32_t nth, uint32_t ch, uint32_t row, uint32_t col) const = 0;
};

} // namespace kernel
} // namespace misc
} // namespace nnfw

#endif // __NNFW_MISC_KERNEL_READER_H__
