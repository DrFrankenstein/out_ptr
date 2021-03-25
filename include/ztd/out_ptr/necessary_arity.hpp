// Copyright ⓒ 2018-2021 ThePhD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//  See https://github.com/ThePhD/out_ptr/blob/master/docs/out_ptr.adoc for documentation.

#pragma once

#ifndef ZTD_OUT_PTR_NECESSARY_ARITY_HPP
#define ZTD_OUT_PTR_NECESSARY_ARITY_HPP

#include <ztd/out_ptr/detail/customization_forward.hpp>
#include <ztd/out_ptr/detail/is_specialization_of.hpp>

#include <type_traits>
#include <memory>

namespace ztd {
namespace out_ptr {
	namespace op_detail {
		template <typename Smart, typename... Args>
		class necessary_arity_impl : public std::integral_constant<std::size_t, static_cast<std::size_t>(is_specialization_of<Smart, std::shared_ptr>::value || is_specialization_of<Smart, boost::shared_ptr>::value)> {};
	} // namespace op_detail

	template <typename Smart, typename... Args>
	class necessary_arity : public op_detail::necessary_arity_impl<Smart, Args...> {};

#if defined(__cpp_inline_variables) && (!defined(__clang__) || __cplusplus > 201400L)
	template <typename Smart, typename... Args>
	inline static constexpr std::size_t necessary_arity_v = necessary_arity<Smart, Args...>::value;
#elif defined(__cpp_alias_templates) && (!defined(__clang__) || __cplusplus > 201100L)
	template <typename Smart, typename... Args>
	static constexpr std::size_t necessary_arity_v = necessary_arity<Smart, Args...>::value;
#endif
}
} // namespace ztd::out_ptr

#endif // ZTD_OUT_PTR_NECESSARY_ARITY_HPP
