#pragma once
/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */

#include <stdio.h>
#include <stropt.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

int _kbhit();
