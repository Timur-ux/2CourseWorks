#ifndef REALIZATION_TYPE
#define REALIZATION_TYPE

inline int realizationType = 0;

__declspec(dllexport) int realizationChange() {
	realizationType = (int)not(realizationType);
	return realizationType;
}

#endif