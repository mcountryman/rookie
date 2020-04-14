//
// Created by maarvin on 4/8/20.
//

#ifndef ROOKIE_FORMAT_HPP
#define ROOKIE_FORMAT_HPP

#include <string>

std::string format(const char *fmt, ...)
#ifdef __GNUC__
__attribute__ ((format (printf, 1, 2)))
#endif
;

#endif //ROOKIE_FORMAT_HPP
