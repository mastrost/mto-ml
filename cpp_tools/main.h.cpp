#include "./main.h"
#include <stdexcept>
#include <cstdio>
#include <string>

static int (*g_main)(int argc, char const **argv) = nullptr;

#include "cpp_tools/defines.h"//[mto]
namespace mto::cpp_tools {//[mto.ns_begin]
using namespace std;
main_function_registerer_t::main_function_registerer_t(int (*f)(int argc, char const **argv)) {
  g_main = f;
}

}//[mto.ns_end]

int main(int argc, char const **argv) {
  try {
    CHECK(g_main);
    return g_main(argc, argv);
    return 0;
  } catch (std::exception const &e) {
    fprintf(stderr, "%s\n", e.what());
    return 1;
  } catch (std::string const &str) {
    fprintf(stderr, "%s\n", str.c_str());
    return 1;
  } catch (char const *str) {
    fprintf(stderr, "%s\n", str);
    return 1;
  } catch (...) {
    fprintf(stderr, "Unknown error\n");
    return 1;
  }
}
