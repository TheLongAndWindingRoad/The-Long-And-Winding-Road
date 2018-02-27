#ifndef MACRO_H
#define	MACRO_H

template<typename T>
inline void SafeRelease(T*& _type)
{
	if (_type != nullptr)
	{
		(_type)->Release();
		(_type) = nullptr;
	}
}

template<typename T>
inline void SafeDelete(T*& _type)
{
	if (_type != nullptr)
	{
		delete _type;
		(_type) = nullptr;
	}
}

template<typename T>
inline void SafeDeleteArray(T*& _type)
{
	if (_type != nullptr)
	{
		delete[] _type;
		(_type) = nullptr;
	}
}
#endif