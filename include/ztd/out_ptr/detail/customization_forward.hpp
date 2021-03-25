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

#ifndef ZTD_OUT_PTR_DETAIL_CUSTOMIZATION_FORWARD_HPP
#define ZTD_OUT_PTR_DETAIL_CUSTOMIZATION_FORWARD_HPP

namespace boost {

	namespace movelib {
		template <typename, typename>
		class unique_ptr;
	}

	template <typename>
	class shared_ptr;

} // namespace ztd

#endif // ZTD_OUT_PTR_DETAIL_CUSTOMIZATION_FORWARD_HPP