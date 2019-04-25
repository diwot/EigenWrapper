#pragma once

namespace EigenWrapper
{
	template<class T>
	class NativeData
	{
	public:
		T Data;

		template<class T>
		NativeData(T&& data) : Data(data)
		{ }
	};
}

