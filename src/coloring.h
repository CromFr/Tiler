#ifndef COLORING_H_INCLUDED
#define COLORING_H_INCLUDED

#include <iostream>

#define CLR_TYPO_BOLD	"\e[1m"

#define CLR_FG_BLACK	"\e[30m"
#define CLR_FG_RED		"\e[31m"
#define CLR_FG_GREEN	"\e[32m"
#define CLR_FG_YELLOW	"\e[33m"
#define CLR_FG_BLUE		"\e[34m"
#define CLR_FG_MAJENTA	"\e[35m"
#define CLR_FG_CYAN		"\e[36m"
#define CLR_FG_WHITE	"\e[37m"

#define CLR_BG_BLACK	"\e[40m"
#define CLR_BG_RED		"\e[41m"
#define CLR_BG_GREEN	"\e[42m"
#define CLR_BG_YELLOW	"\e[43m"
#define CLR_BG_BLUE		"\e[44m"
#define CLR_BG_MAJENTA	"\e[45m"
#define CLR_BG_CYAN		"\e[46m"
#define CLR_BG_WHITE	"\e[47m"

#define CLR_END			"\e[m"

#define CLR_WARNING		"\e[1;33m"
#define CLR_ERROR		"\e[1;31m;40m"
#define CLR_INFO		"\e[36m"
#define CLR_SUCCESS		"\e[1;32m"
#define CLR_FAILED		"\e[1;31m"

#define cErr			std::cerr<<"\e[1;31;40mError:   \e[m\e[36m"<<__PRETTY_FUNCTION__<<"\e[m: "
#define cWar			std::cerr<<"\e[1;33mWarning: \e[m\e[36m"<<__PRETTY_FUNCTION__<<"\e[m: "
#define cInf			std::clog<<"\e[36mInfo:    \e[m"
#define cSuc			std::clog<<"\e[1;32mSuccess: \e[m"
#define cFai			std::clog<<"\e[1;31mFail:    \e[m"


#endif // COLORING_H_INCLUDED
