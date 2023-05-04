/**
 * @file constexpr_parameter.hpp
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

// Cast to the real constant variable
#define to_constexpr(X)                                                                                                                              \
  meta::ConstexprParameter<X> {}

// Namespace for ConstexprVariable
namespace meta {

/**
 * @brief Template to convert value to constexpr
 *
 * @tparam tpVal
 */
template <const auto variable> struct ConstexprParameter final {
  static constexpr auto value = variable;
  struct ConstexprParameterT {
    using type = void;
  };
};

// Concept for C++20 to check type for ConstexprVariable
#ifdef __cpp_concepts
template <typename T>
concept constexpr_parameter = requires(T) { typename T::ConstexprParameterT; };
#endif

// Type traits for SFINAE to check type for ConstexprVariable
template <typename T, typename U = void> struct is_constexpr {
  static constexpr auto value = false;
};

template <typename T> struct is_constexpr<T, typename T::ConstexprParameterT::type> {
  static constexpr auto value = true;
};

template <typename T> inline constexpr auto is_constexpr_v = is_constexpr<T>::value;

} // namespace meta
