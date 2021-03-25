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

#include <benchmarks/statistics.hpp>

#include <benchmark/benchmark.h>

#define ZTD_OUT_PTR_HAS_FRIENDLY_UNIQUE_PTR 1

#include <benchmarks/out_ptr/friendly_unique_ptr.hpp>
#include <ztd/out_ptr/out_ptr.hpp>
#include <benchmarks/out_ptr/friendly_out_ptr.hpp>

#include <ficapi/ficapi.hpp>

#include <memory>
#include <cstdlib>

static void c_code_reset_out_ptr(benchmark::State& state) {
	int64_t x			   = 0;
	ficapi_opaque_handle p = NULL;
	for (auto _ : state) {
		(void)_;
		if (p != NULL) {
			ficapi_handle_no_alloc_delete(p);
		}
		ficapi_handle_no_alloc_create(&p);
		x += ficapi_handle_get_data(p);
	}
	if (p != NULL) {
		ficapi_handle_no_alloc_delete(p);
	}
}
BENCHMARK(c_code_reset_out_ptr)

	->ComputeStatistics("max", &compute_max)
	->ComputeStatistics("min", &compute_min)
	->ComputeStatistics("dispersion", &compute_index_of_dispersion);

static void manual_reset_out_ptr(benchmark::State& state) {
	int64_t x = 0;
	std::unique_ptr<ficapi::opaque, ficapi::handle_no_alloc_deleter> p(nullptr);
	for (auto _ : state) {
		(void)_;
		ficapi_opaque_handle temp_p = NULL;
		ficapi_handle_no_alloc_create(&temp_p);
		p.reset(temp_p);
		x += ficapi_handle_get_data(p.get());
	}
	int64_t expected = int64_t(state.iterations()) * ficapi_get_data();
	if (x != expected) {
		state.SkipWithError("Unexpected result");
		return;
	}
}
BENCHMARK(manual_reset_out_ptr)

	->ComputeStatistics("max", &compute_max)
	->ComputeStatistics("min", &compute_min)
	->ComputeStatistics("dispersion", &compute_index_of_dispersion);

static void simple_reset_out_ptr(benchmark::State& state) {
	int64_t x = 0;
	std::unique_ptr<ficapi::opaque, ficapi::handle_no_alloc_deleter> p(nullptr);
	for (auto _ : state) {
		(void)_;
		ficapi_handle_no_alloc_create(ztd::out_ptr::op_detail::simple_out_ptr(p));
		x += ficapi_handle_get_data(p.get());
	}
	int64_t expected = int64_t(state.iterations()) * ficapi_get_data();
	if (x != expected) {
		state.SkipWithError("Unexpected result");
		return;
	}
}
BENCHMARK(simple_reset_out_ptr)

	->ComputeStatistics("max", &compute_max)
	->ComputeStatistics("min", &compute_min)
	->ComputeStatistics("dispersion", &compute_index_of_dispersion);

static void clever_reset_out_ptr(benchmark::State& state) {
	int64_t x = 0;
	std::unique_ptr<ficapi::opaque, ficapi::handle_no_alloc_deleter> p(nullptr);
	for (auto _ : state) {
		(void)_;
		ficapi_handle_no_alloc_create(ztd::out_ptr::op_detail::clever_out_ptr(p));
		x += ficapi_handle_get_data(p.get());
	}
	int64_t expected = int64_t(state.iterations()) * ficapi_get_data();
	if (x != expected) {
		state.SkipWithError("Unexpected result");
		return;
	}
}
BENCHMARK(clever_reset_out_ptr)

	->ComputeStatistics("max", &compute_max)
	->ComputeStatistics("min", &compute_min)
	->ComputeStatistics("dispersion", &compute_index_of_dispersion);


#if defined(ZTD_OUT_PTR_HAS_FRIENDLY_UNIQUE_PTR) && ZTD_OUT_PTR_HAS_FRIENDLY_UNIQUE_PTR != 0

static void friendly_reset_out_ptr(benchmark::State& state) {
	int64_t x = 0;
	std::friendly_unique_ptr<ficapi::opaque, ficapi::handle_no_alloc_deleter> p(nullptr);
	for (auto _ : state) {
		(void)_;
		ficapi_handle_no_alloc_create(ztd::out_ptr::friendly_out_ptr(p));
		x += ficapi_handle_get_data(p.get());
	}
	int64_t expected = int64_t(state.iterations()) * ficapi_get_data();
	if (x != expected) {
		state.SkipWithError("Unexpected result");
		return;
	}
}
BENCHMARK(friendly_reset_out_ptr)

	->ComputeStatistics("max", &compute_max)
	->ComputeStatistics("min", &compute_min)
	->ComputeStatistics("dispersion", &compute_index_of_dispersion);

#endif // OUT_PTR_HAS_FRIENDLY_UNIQUE_PTR
