// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __TESTS_UTILS_HPP__
#define __TESTS_UTILS_HPP__

#include <stdint.h>

#include <string>

#include <stout/ip.hpp>
#include <stout/json.hpp>
#include <stout/try.hpp>

namespace mesos {
namespace internal {
namespace tests {

// Get the metrics snapshot.
// TODO(vinod): Move this into a libprocess utility header.
JSON::Object Metrics();

// Path finding utilities.
//
// Various tests need to access paths to load files or libraries. Normally,
// these paths are located within the build directory, often in the .libs
// directories generated by Automake. However, if the Mesos tests were built
// with --enable-tests-install, we may be running the tests from an installed
// version of the test suite. In this case, we should always find paths in the
// installation tree and never the build directory. If the build directory is
// still present, you can force these helpers to ignore it by passing the
// --build_dir=/none option to the test suite.
//
// The path helpers below all check for a build directory path, then fall back
// to an installation path only if --enable-tests-install was specified at
// configuration time.

// Get the path to a named Mesos module.
std::string getModulePath(const std::string& name);

// Get the path to libmesos-$(VERSION).so
std::string getLibMesosPath();

// Get the launcher directory for mesos-executor, mesos-containerizer, etc.
std::string getLauncherDir();

// Get the path to a named test helper.
std::string getTestHelperPath(const std::string& name);

// Get the path to a named test script. In the Mesos source tree,
// these live in $MESOS_SOURCE_DIR/src/tests. In a tests install
// they live in $TESTLIBEXECDIR.
std::string getTestScriptPath(const std::string& name);

// Get the path to the directory where test helpers are installed.
std::string getTestHelperDir();

// Get the path to the directory where executables that require super-
// user privileges are installed.
std::string getSbinDir();

// Get the path to the directory of the webui files/assets.
std::string getWebUIDir();

// Get a random unused port.
//
// NOTE: While we make sure that the port returned by this function is
// unused when this function returns, it might become used before the
// caller can bind to it.
Try<uint16_t> getFreePort();

// Get a non-loopback IP available on this host.
Try<net::IPNetwork> getNonLoopbackIP();

} // namespace tests {
} // namespace internal {
} // namespace mesos {

#endif // __TESTS_UTILS_HPP__
