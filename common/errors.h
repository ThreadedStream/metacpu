#pragma once

enum {
    FAILED_TO_INIT_STREAM,
    FAILED_TO_READ_PREAMBLE,
    FAILED_TO_READ_CONTENTS,
    FAILED_TO_ALLOCATE_MEMORY,
    MALFORMED_PREAMBLE,
};

static const char *errors[] = {
        "failed to initialize stream\n",
        "failed to read preamble\n",
        "failed to read contents from a file\n",
        "failed to allocate memory\n",
        "malformed preamble\n",
};
