#include "./main.h"
#include <stdexcept>
#include <cstdio>
#include <string>

static int (*g_main)(int argc, char const **argv) = nullptr;

#include "cpp_tools/defines.h"
namespace mto::cpp_tools {
using namespace std;
main_function_registerer_t::main_function_registerer_t(int (*f)(int argc, char const **argv)) {
  g_main = f;
}

}

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
