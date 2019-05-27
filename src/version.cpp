#include "version.h"

int major_version() {
    return version.major;
}

int minor_version() {
    return version.minor;
}

int patch_version() {
    return version.patch;
}
