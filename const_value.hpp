/**
 * @file const_value.hpp
 * @author Ivan Sobchuk (i.a.sobchuk.1994@gmail.com)
 * @brief Simple template to convert function's parameters from
 * non-type template to constexpr. Supported from C++17 and higher.
 *
 * @date 2023-05-04
 *
 * @copyright Ivan Sobchuk (c) 2023
 *
 * License Apache 2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#pragma once

// Suppoted since C++17 as a last fully-supported standard for gcc and clang
static_assert((__cplusplus >= 201703L), "Supported only with C++17 and newer!");

// Namespace for ConstValue (The meta framework for embedded, chosen to not cross the existing ones)
namespace iso {

/**
 * @brief Template to convert value to constexpr
 *
 * @tparam param: Value that will be casted to constexpr
 */
template <const auto param> struct ConstValue final {
  using type = decltype(param);
  static constexpr auto value = param;
  struct ConstValueT {
    using type = void;
  };
};

// Cast to the real const value
template <const auto value> inline constexpr auto const_v = ConstValue<value>{};
// Cast to the real const type
template <const auto value> using const_t = ConstValue<value>;

// Concept for C++20 to check type for ConstValue
#ifdef __cpp_concepts
template <typename T>
concept const_value = requires(T) {
  typename T::ConstValueT;
  T::value;
  typename T::type;
};
#endif

// Type traits for SFINAE to check type for ConstValue
template <typename T, typename U = void> struct is_const {
  static constexpr auto value = false;
};

template <typename T> struct is_const<T, typename T::ConstValueT::type> {
  static constexpr auto value = true;
};

template <typename T> inline constexpr auto is_const_v = is_const<T>::value;

} // namespace iso
